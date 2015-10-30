#ifndef PROPITIOUS_MATH_FUNCTIONS_COMMON_HPP
#define PROPITIOUS_MATH_FUNCTIONS_COMMON_HPP

#include <Propitious/Math/Angle.hpp>

#include <algorithm>

namespace Propitious
{
	// Trigonometric
	inline f32 sin(const Radian& theta);
	inline f32 cos(const Radian& theta);
	inline f32 tan(const Radian& theta);

	inline Radian asin(f32 a);
	inline Radian acos(f32 a);
	inline Radian atan(f32 a);
	inline Radian atan2(f32 y, f32 x);

	// Hyperbolic
	inline f32 sinh(f32 x);
	inline f32 cosh(f32 x);
	inline f32 tanh(f32 x);

	inline f32 asinh(f32 x);
	inline f32 acosh(f32 x);
	inline f32 atanh(f32 x);

	// Power
	inline f32 pow(f32 x, f32 y);
	inline f32 sqrt(f32 x);
	inline f32 cbrt(f32 x);
	inline f32 hypotenuse(f32 x, f32 y);

	inline f32 fastInvSqrt(f32 x);

	// Exponential and Logarithm
	inline f32 exp(f32 x);  // e^x
	inline f32 exp2(f32 x); // 2^x
	inline f32 ln(f32 x);
	inline f32 ln1p(f32 x); // ln(1 + x)
	inline f32 log2(f32 x);
	inline f32 log10(f32 x);
	inline f32 logBase(f32 x, f32 base);

	// Rounding
	inline f32 ceil(f32 x);
	inline f32 floor(f32 x);
	inline f32 mod(f32 x, f32 y);
	inline f32 truncate(f32 x);
	inline f32 round(f32 x);

	inline i32 sign(i32 x);
	inline i64 sign(i64 x);
	inline f32 sign(f32 x);

	// Other
	inline f32 abs(f32 x);
	inline i8  abs(i8 x);
	inline i16 abs(i16 x);
	inline i32 abs(i32 x);
	inline i64 abs(i64 x);

	inline Radian abs(const Radian& x);
	inline Degree abs(const Degree& x);

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
	inline T clamp(const T& x, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(x, upper));
	}

	template <class T>
	inline T kroneckerDelta(const T& i, const T& j)
	{
		return i == j ? T(1) : T(0);
	}
} // namespace Propitious

#endif
