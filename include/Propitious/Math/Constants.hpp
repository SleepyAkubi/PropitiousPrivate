#ifndef PROPITIOUS_MATH_CONSTANTS_HPP
#define PROPITIOUS_MATH_CONSTANTS_HPP

#include <Propitious/Common.hpp>
#include <limits>

namespace Propitious
{
	template <class T>
	struct propexp Constants
	{
		static  T Epsilon() { return std::numeric_limits<T>::epsilon(); }

		static  T One();
		static  T Zero();
		static  T Third();
		static  T TwoThirds();

		static  T E();
		static  T Pi();
		static  T Tau();

		static  T Sqrt2();
		static  T Sqrt3();
		static  T Sqrt5();

		static  T GoldenRatio();

		static T Bit() { return (T)1; }
		static T Byte() { return (T)8; }

#ifndef RUBBISH_METRIC_UNITS
		static T KilobyteAsBytes()  { return (T)(1024 ^ 1); }
		static T MegabyteAsBytes()  { return (T)(1024 ^ 2); }
		static T GigabyteAsBytes()  { return (T)(1024 ^ 3); }
		static T TerabyteAsBytes()  { return (T)(1024 ^ 4); }
		static T PetabyteAsBytes()  { return (T)(1024 ^ 5); }
		static T ExabyteAsBytes()   { return (T)(1024 ^ 6); }
		static T ZetabyteAsBytes()  { return (T)(1024 ^ 7); }
		static T YottabyteAsBytes() { return (T)(1024 ^ 8); }
#else
		#pragma message("You are insane.")
		static T KilobyteAsBytes()  { return (T)(1000 ^ 1); }
		static T MegabyteAsBytes()  { return (T)(1000 ^ 2); }
		static T GigabyteAsBytes()  { return (T)(1000 ^ 3); }
		static T TerabyteAsBytes()  { return (T)(1000 ^ 4); }
		static T PetabyteAsBytes()  { return (T)(1000 ^ 5); }
		static T ExabyteAsBytes()   { return (T)(1000 ^ 6); }
		static T ZetabyteAsBytes()  { return (T)(1000 ^ 7); }
		static T YottabyteAsBytes() { return (T)(1000 ^ 8); }
#endif

		static T KilobyteAsBits()  { return (T)(KilobyteAsBytes()  * 8); }
		static T MegabyteAsBits()  { return (T)(MegabyteAsBytes()  * 8); }
		static T GigabyteAsBits()  { return (T)(GigabyteAsBytes()  * 8); }
		static T TerabyteAsBits()  { return (T)(TerabyteAsBytes()  * 8); }
		static T PetabyteAsBits()  { return (T)(PetabyteAsBytes()  * 8); }
		static T ExabyteAsBits()   { return (T)(ExabyteAsBytes()   * 8); }
		static T ZetabyteAsBits()  { return (T)(ZetabyteAsBytes()  * 8); }
		static T YottabyteAsBits() { return (T)(YottabyteAsBytes() * 8); }
	};

	template<>
	struct propexp Constants<f32>
	{
		Constants() = delete;

		static  f32 Epsilon() { return std::numeric_limits<f32>::epsilon(); }

		static  f32 One() { return 1.0f; }
		static  f32 Zero() { return 0.0f; }
		static  f32 Third() { return 0.333333333f; }
		static  f32 TwoThirds() { return 0.666666667f; }

		static  f32 E() { return 2.718281828f; }
		static  f32 Pi() { return 3.141592654f; }
		static  f32 Tau() { return 6.283185307f; }

		static  f32 Sqrt2() { return 1.414213562f; }
		static  f32 Sqrt3() { return 1.732050808f; }
		static  f32 Sqrt5() { return 2.236067978f; }

		static  f32 GoldenRatio() { return 1.618033989f; }
	};

	template<>
	struct propexp Constants<f64>
	{
		Constants() = delete;

		static  f64 Epsilon() { return std::numeric_limits<f64>::epsilon(); }

		static  f64 One() { return 1.0; }
		static  f64 Zero() { return 0.0; }
		static  f64 Third() { return 0.333333333333333; }
		static  f64 TwoThirds() { return 0.666666666666667; }

		static  f64 E() { return 2.718281828459045; }
		static  f64 Pi() { return 3.141592653589793; }
		static  f64 Tau() { return 6.283185307179586; }

		static  f64 Sqrt2() { return 1.414213562373095; }
		static  f64 Sqrt3() { return 1.732050807568877; }
		static  f64 Sqrt5() { return 2.236067977499790; }

		static  f64 GoldenRatio() { return 1.618033988749895; }
	};
}

#endif
