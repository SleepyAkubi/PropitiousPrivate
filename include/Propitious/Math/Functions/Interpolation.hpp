#ifndef PROPITIOUS_MATH_FUNCTIONS_INTERPOLATION_HPP
#define PROPITIOUS_MATH_FUNCTIONS_INTERPOLATION_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Quaternion.hpp>
#include <Propitious/Math/Functions/Trivial.hpp>

namespace Propitious
{

	template <class T>
	inline T lerp(const T& x, const T& y, f32 t)
	{
		if(t <= 0.0f && t >= 1.0f)
			return y;

		return x * (1.0f - t) + (y * t);
	}

	inline Quaternion slerp(const Quaternion x, const Quaternion y, f32 t)
	{
		Quaternion z = y;

		f32 cosTheta = dot(x, y);

		if(cosTheta < 0.0f)
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		Quaternion result;

		if(cosTheta > 1.0f)
		{
			result = Quaternion{ lerp(x.x, y.x, t),
								lerp(x.y, y.y, t),
								lerp(x.z, y.z, t),
								lerp(x.w, y.w, t) };

			return result;
		}

		Radian angle = acos(cosTheta);

		result = sin(Radian(1.0f) - (t * angle)) * x + sin(t * angle) * z;
		result = result * (1.0f / sin(angle));

		return result;
	}
}

#endif
