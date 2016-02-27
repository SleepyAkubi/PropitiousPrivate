#version 120

struct Material
{
	sampler2D diffuseMap;
	vec4 diffuseColour;

	vec4 specularColour;
	float specularExponent;
};

struct Transform
{
	vec3 position;
	vec4 orientation;
	vec3 scale;
};

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct PointLight
{
	vec3 position;
	vec3 intensities;
	/*vec3 ambientCoefficient;*/
	Attenuation attenuation;

	float range;
};

vec3 quaternionRotate(vec4 q, vec3 v)
{
	vec3 t = 2.0 * cross(q.xyz, v);
	return (v + q.w * t + cross(q.xyz, t));
}

vec4 conjugate(vec4 q)
{
	return vec4(-q.xyz, q.w);
}

uniform vec3 u_cameraPosition;
uniform Transform u_transform; //= {vec3(0), vec4(0, 0, 0, 1), vec3(1)};

uniform Material u_material;

uniform float u_gamma = 1.0 / 2.2;

uniform PointLight u_light;

varying vec3 v_position;
varying vec3 v_colour;
varying vec2 v_texCoord;
varying vec3 v_normal;

void main()
{
	vec4 texColour = texture2D(u_material.diffuseMap, v_texCoord).rgba;
	//if(texColour.a < 0.5)
	//	discard;

	vec3 surfaceColour = u_material.diffuseColour.rgb * texColour.rgb * v_colour;

	vec3 normal = normalize(quaternionRotate(u_transform.orientation, v_normal));
	vec3 gamma = vec3(1.0/u_gamma);

	vec3 surfaceToLight = normalize(u_light.position - v_position);
	float distanceToLight = length(u_light.position - v_position);

	float attenuation = 1.0 / (u_light.attenuation.constant
														 + u_light.attenuation.linear
														 * distanceToLight
														 + u_light.attenuation.quadratic
														 * distanceToLight
														 * distanceToLight);

	// nicked from Unreal Engine 4, because it works.
	attenuation *= clamp(pow(1 - pow(distanceToLight / u_light.range, 4.0), 2.0), 0, 1);

	vec3 surfaceToCamera = normalize(u_cameraPosition - v_position);

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
	float specularCoefficient = 0.0;

	if (diffuseCoefficient > 0.0)
		specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), u_material.specularExponent);

	vec3 diffuseComponent  = diffuseCoefficient  * u_light.intensities.rgb;
	vec3 specularComponent = specularCoefficient * u_light.intensities.rgb * u_material.specularColour.rgb;

	vec3 finalColour = (diffuseComponent.rgb + specularComponent.rgb) * attenuation * surfaceColour.rgb;

	gl_FragColor = vec4(pow(finalColour, gamma), 1.0);
}
