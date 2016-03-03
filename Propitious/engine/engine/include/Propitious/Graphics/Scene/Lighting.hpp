#ifndef PROPITIOUS_GRAPHICS_SCENE_LIGHTING_HPP
#define PROPITIOUS_GRAPHICS_SCENE_LIGHTING_HPP

#include <Propitious/Common.hpp>

#include <Propitious/Graphics/Colour.hpp>
#include <Propitious/Math/Angle.hpp>
#include <Propitious/Math/Functions/Trivial.hpp>
#include <Propitious/Math/Vector3.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT Attenuation
	{
		f32 constant = 1.0f;
		f32 linear = 0.0f;
		f32 quadratic = 1.0f;
	};

	struct PROPITIOUS_EXPORT BaseLight
	{
		Colour colour = Colour{ 255, 255, 255 };
		f32 brightness = 1.0f;
	};

	struct PROPITIOUS_EXPORT DirectionalLight : BaseLight
	{
		Vector3 direction;
	};

	struct PROPITIOUS_EXPORT PointLight : BaseLight
	{
		Vector3 position = { 0, 0, 0 };
		mutable f32 range = 16.0f;

		Attenuation attenuation;

		inline void calculateRange() const
		{
			f32 i = brightness * (f32)Math::maximum(colour.r, Math::maximum(colour.g, colour.b));

			f32 r = -attenuation.linear +
				Math::sqrt(attenuation.linear * attenuation.linear -
					4.0f * attenuation.quadratic *
					(attenuation.constant - i));
			r /= 2.0f * attenuation.quadratic;

			range = r;
		}
	};

	struct PROPITIOUS_EXPORT SpotLight : PointLight
	{
		Radian coneAngle = Radian(Degree(20));
		Vector3 direction = Vector3{ 0, 0, -1 };
	};
}

#endif
