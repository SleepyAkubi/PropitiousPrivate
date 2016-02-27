#ifndef PROPITIOUS_MATH_FUNCTIONS_TRIVIAL_HPP
#define PROPITIOUS_MATH_FUNCTIONS_TRIVIAL_HPP

#include <Propitious/Math/Angle.hpp>

#include <algorithm>
#include <cfenv>

namespace Propitious
{
	namespace Math
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

		inline f32 sin(const Radian& theta) { return std::sin((f32)(theta)); }
		inline f32 cos(const Radian& theta) { return std::cos((f32)(theta)); }
		inline f32 tan(const Radian& theta) { return std::tan((f32)(theta)); }

		inline Radian asin(f32 a) { return Radian(std::asin(a)); }
		inline Radian acos(f32 a) { return Radian(std::acos(a)); }
		inline Radian atan(f32 a) { return Radian(std::atan(a)); }
		inline Radian atan2(f32 y, f32 x) { return Radian(std::atan2(y, x)); }

		// Hyperbolic
		inline f32 sinh(f32 x) { return std::sinh(x); }
		inline f32 cosh(f32 x) { return std::cosh(x); }
		inline  f32 tanh(f32 x) { return std::tanh(x); }

		inline f32 asinh(f32 x) { return std::asinh(x); }
		inline f32 acosh(f32 x) { return std::acosh(x); }
		inline f32 atanh(f32 x) { return std::atanh(x); }

		// Power
		inline f32 cubepow(f32 x, f32 y) { return std::pow(x, y); }

		inline f32 sqrt(f32 x) { return std::sqrt(x); }

		inline f32 cbrt(f32 x) { return std::cbrt(x); }

		inline f32 hypotenuse(f32 x, f32 y) { return std::hypot(x, y); }

		inline f32 fastInvSqrt(f32 number)
		{
			u32 i;
			f32 x2, y;
			const f32 threeHalfs = 1.5f;

			x2 = number * 0.5f;
			y = number;
			i = pseudo_cast<u32>(y);
			i = 0x5f375a86 - (i >> 1);
			y = pseudo_cast<f32>(i);
			y = y * (threeHalfs - (x2 * y * y));

			return y;
		}

		inline f32 exp(f32 x) // e^x
		{
			return std::exp(x);
		}
		inline f32 exp2(f32 x) // 2^x
		{
			return std::exp2(x);
		}
		inline f32 ln(f32 x) { return std::log(x); }
		inline f32 ln1p(f32 x) // ln(1 + x)
		{
			return std::log1p(x);
		}
		inline f32 log2(f32 x) { return std::log2(x); }

		inline f32 log10(f32 x) { return std::log10(x); }
		inline f32 logBase(f32 x, f32 base) { return ln(x) * (1.0f / ln(base)); }

		// Rounding
		inline f32 ceil(f32 x) { return std::ceil(x); }
		inline f32 floor(f32 x) { return std::floor(x); }
		inline f32 mod(f32 x, f32 y)
		{
			f32 result = std::remainder(abs(x), (y = abs(y)));
			if (std::signbit(result))
				result += y;
			return std::copysign(result, x);
		}
		inline f32 truncate(f32 x)
		{
			u32 i = pseudo_cast<u32>(x);
			i32 exponent = (i >> 23) & 0xFF; // extract exponent field
			i32 fractionalBits = 0x7F + 23 - exponent;
			if (fractionalBits > 23) // abs(x) < 1.0f
				return 0.0f;
			if (fractionalBits > 0)
				i &= ~((1u << fractionalBits) - 1);
			return pseudo_cast<f32>(i);
		}
		inline f32 round(f32 x)
		{
			std::fenv_t saveEnv;
			std::feholdexcept(&saveEnv);
			f32 result = std::rint(x);
			if (std::fetestexcept(FE_INEXACT))
			{
				std::fesetround(FE_TOWARDZERO);
				result = std::rint(std::copysign(0.5f + abs(x), x));
			}
			std::feupdateenv(&saveEnv);
			return result;
		}

		inline i32 sign(i32 x)
		{
			u32 i = reinterpret_cast<const u32&>(x);
			i &= 0x80000000ul;
			if (i)
				return -1;
			return 1;
		}

		inline i64 sign(i64 x)
		{
			u64 i = reinterpret_cast<const u64&>(x);
			i &= 0x8000000000000000ull;
			if (i)
				return -1;
			return 1;
		}

		inline f32 sign(f32 x)
		{
			u32 i = reinterpret_cast<const u32&>(x);
			i &= 0x80000000ul;
			if (i)
				return -1.0f;
			return 1.0f;
		}

		// Other
		inline f32 abs(f32 x)
		{
			u32 i = reinterpret_cast<const u32&>(x);
			i &= 0x7FFFFFFFul;
			return reinterpret_cast<const f32&>(i);
		}
		inline i8 abs(i8 x)
		{
			u8 i = reinterpret_cast<const u8&>(x);
			i &= 0x7Fu;
			return reinterpret_cast<const i8&>(i);
		}
		inline i16 abs(i16 x)
		{
			u16 i = reinterpret_cast<const u16&>(x);
			i &= 0x7FFFu;
			return reinterpret_cast<const i16&>(i);
		}
		inline i32 abs(i32 x)
		{
			u32 i = reinterpret_cast<const u32&>(x);
			i &= 0x7FFFFFFFul;
			return reinterpret_cast<const i32&>(i);
		}
		inline i64 abs(i64 x)
		{
			u64 i = reinterpret_cast<const u64&>(x);
			i &= 0x7FFFFFFFFFFFFFFFull;
			return reinterpret_cast<const i64&>(i);
		}

		inline Radian abs(const Radian& x)
		{
			return Radian(abs((f32)(x)));
		}

		inline Degree abs(const Degree& x)
		{
			return Degree(abs((f32)(x)));
		}


		template <class T>
		inline const T& maximum(const T& a, const T& b)
		{
			return (a > b) ? a : b;
		}

		template <class T>
		inline const T& minimum(const T& a, const T& b)
		{
			return (a > b) ? b : a;
		}

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
			return max(lower, min(x, upper));
		}

		template <class T>
		inline T kroneckerDelta(const T& i, const T& j)
		{
			return i == j ? T(1) : T(0);
		}
	}
} // namespace Propitious

#endif
