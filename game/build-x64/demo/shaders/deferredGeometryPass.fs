#version 120

#include <common.sp>
#include <material.sp>

uniform vec3 u_cameraPosition;
uniform Transform u_transform;

uniform Material u_material;

varying vec3 v_position;
varying vec3 v_colour;
varying vec2 v_texCoord;
varying vec3 v_normal;
varying mat3 v_tbnMatrixInv;

void main()
{
	vec4 texColour = texture2D(u_material.diffuseMap, v_texCoord).rgba;

	if(texColour.a < 0.5)
		discard;

	vec3 surfaceColour = u_material.diffuseColour.rgb * texColour.rgb * v_colour;


	vec3 normal = normalize((255.0/128.0) * texture2D(u_material.normalMap, v_texCoord).xyz - vec3(1, 1, 1));
	normal = v_tbnMatrixInv * normal;


	gl_FragData[0].rgb = surfaceColour.rgb;
	gl_FragData[1].rgb = u_material.specularColour.rgb;
  gl_FragData[2].xyz = 0.5 * (normal + vec3(1.0));
}
