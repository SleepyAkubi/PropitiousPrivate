#ifndef MATERIAL_SP
#define MATERIAL_SP

struct Material
{
	sampler2D diffuseMap;
	vec4 diffuseColour;

	sampler2D normalMap;

	vec4 specularColour;
	float specularExponent;
};

#endif
