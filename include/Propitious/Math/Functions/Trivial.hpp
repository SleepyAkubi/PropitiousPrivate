#ifndef PROPITIOUS_MATH_FUNCTIONS_COMMON_HPP
#define PROPITIOUS_MATH_FUNCTIONS_COMMON_HPP

#include <Propitious/Math/Angle.hpp>

#include <algorithm>

namespace Propitious
{
	// Trigonometric
	propexp f32 sin(const Radian& theta);
	propexp f32 cos(const Radian& theta);
	propexp f32 tan(const Radian& theta);

	propexp Radian asin(f32 a);
	propexp Radian acos(f32 a);
	propexp Radian atan(f32 a);
	propexp Radian atan2(f32 y, f32 x);

	// Hyperbolic
	propexp f32 sinh(f32 x);
	propexp f32 cosh(f32 x);
	propexp f32 tanh(f32 x);

	propexp f32 asinh(f32 x);
	propexp f32 acosh(f32 x);
	propexp f32 atanh(f32 x);

	// Power
	propexp f32 pow(f32 x, f32 y);
	propexp f32 sqrt(f32 x);
	propexp f32 cbrt(f32 x);
	propexp f32 hypotenuse(f32 x, f32 y);

	propexp f32 fastInvSqrt(f32 x);

	// Exponential and Logarithm
	propexp f32 exp(f32 x);  // e^x
	propexp f32 exp2(f32 x); // 2^x
	propexp f32 ln(f32 x);
	propexp f32 ln1p(f32 x); // ln(1 + x)
	propexp f32 log2(f32 x);
	propexp f32 log10(f32 x);
	propexp f32 logBase(f32 x, f32 base);

	// Rounding
	propexp f32 ceil(f32 x);
	propexp f32 floor(f32 x);
	propexp f32 mod(f32 x, f32 y);
	propexp f32 truncate(f32 x);
	propexp f32 round(f32 x);

	propexp i32 sign(i32 x);
	propexp i64 sign(i64 x);
	propexp f32 sign(f32 x);

	// Other
	propexp f32 abs(f32 x);
	propexp i8  abs(i8 x);
	propexp i16 abs(i16 x);
	propexp i32 abs(i32 x);
	propexp i64 abs(i64 x);

	propexp Radian abs(const Radian& x);
	propexp Degree abs(const Degree& x);

	inline f32 square(f32 squaree)
	{
		return squaree * squaree;
	}

	inline f32 cube(f32 cubee)
	{
		return cubee * cubee* cubee;
	}

	inline f32 quad(f32 quadee)
	{
		return quadee * quadee * quadee * quadee;
	}

	inline f32 pent(f32 pentee)
	{
		return pentee * pentee * pentee * pentee * pentee;
	}

	template <class T>
	T clamp(const T& x, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(x, upper));
	}

	template <class T>
	propexp inline T kroneckerDelta(const T& i, const T& j)
	{
		return i == j ? T(1) : T(0);
	}
} // namespace Propitious

#endif
