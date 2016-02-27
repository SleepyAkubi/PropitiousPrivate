#version 120

uniform sampler2D u_diffuse;
uniform sampler2D u_lighting;

uniform float u_gamma;

varying vec2 v_texCoord;

void main()
{
  vec3 diffuseColour = texture2D(u_diffuse, v_texCoord).rgb;
  vec3 lightingColour = texture2D(u_lighting, v_texCoord).rgb;

  vec3 finalColour = diffuseColour * lightingColour;
  vec3 gamma = vec3(u_gamma);

  gl_FragColor = vec4(pow(finalColour, gamma), 1.0);
}
