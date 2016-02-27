#ifndef LIGHTING_SP
#define LIGHTING_SP

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct BaseLight
{
	vec3 intensities;
};

struct DirectionalLight
{
  BaseLight base;

  vec3 direction;
};

struct PointLight
{
	BaseLight base;

	vec3 position;
	/*vec3 ambientCoefficient;*/
	Attenuation attenuation;

	float range;
};

struct SpotLight
{
	PointLight pointLight;

	float coneAngle;
	vec3 direction;
};

#endif
