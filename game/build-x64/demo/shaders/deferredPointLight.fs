#version 120

#include <common.sp>
#include <lighting.sp>

uniform sampler2D u_diffuse;
//uniform sampler2D u_specular;
uniform sampler2D u_normal;
uniform sampler2D u_depth;

uniform mat4 u_cameraInverse;
uniform PointLight u_light;

varying vec2 v_texCoord;

vec4 calculatePointLight(vec3 surfaceToLight, float distanceToLight, vec3 normal)
{
  float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));

	float attenuation =
	    u_light.attenuation.constant +
	    u_light.attenuation.linear * distanceToLight +
	    u_light.attenuation.quadratic * distanceToLight * distanceToLight;
	attenuation = 1.0 / attenuation;

  attenuation *= clamp(
	    square(1.0 - (square(distanceToLight / u_light.range))), 0, 1);

  vec4 diffuse = vec4(0.0);

  diffuse.rgb = diffuseCoefficient * u_light.base.intensities.rgb * attenuation;
  diffuse.a = 1.0;

  return diffuse;
}

void main()
{
  // Get our previously calculated stuff.
  vec3 normalEncoded  = texture2D(u_normal,   v_texCoord).xyz;
  float depth         = texture2D(u_depth,    v_texCoord).r;

  // Calculate this pixel's position from it's depth using fancy homogeneous stuff.
  vec3 position = calculatePosition(v_texCoord, gl_FragCoord.w, depth, u_cameraInverse);
  // Get a vector of normals, then normalize them (just to be sure).
  vec3 normal = normalize(2.0 * normalEncoded - vec3(1.0));

  vec3 surfaceToLight = normalize(u_light.position - position);
  float distanceToLight = length(u_light.position - position);

  vec4 lightColour = calculatePointLight(surfaceToLight, distanceToLight, normal);

  gl_FragColor = vec4(lightColour.rgb, 1.0);
  //gl_FragColor = vec4(pow(lightColour.rgb, gamma), 1.0);
  //gl_FragColor = vec4(lightColour.rgb, 1.0);
  //gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
