#ifndef PROPITIOUS_TYPES_HPP
#define PROPITIOUS_TYPES_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	using a8  = char;
	using a16 = short;
	using a32 = int;
	using a64 = long long;

	using i8  = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	using u8  = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	using f32 = float;
	using f64 = double;

#if !PROPITIOUS_MAXINT_BITS
#elif PROPITIOUS_MAXINT_BITS == 64
	using usize = u64;
#elif PROPITIOUS_MAXINT_BITS == 32
	using usize = u32;
#elif PROPITIOUS_MAXINT_BITS == 16
	using usize = u16;
#elif PROPITIOUS_MAXINT_BITS == 8
	using usize = u8;
#endif

#if !PROPITIOUS_MAXINT_BITS
#elif PROPITIOUS_MAXINT_BITS == 64
	using isize = i64;
#elif PROPITIOUS_MAXINT_BITS == 32
	using isize = i32;
#elif PROPITIOUS_MAXINT_BITS == 16
	using isize = i16;
#elif PROPITIOUS_MAXINT_BITS == 8
	using isize = i8;
#endif

	using iptr = isize;
	using uptr = usize;

	using b8 = bool;
}

#endif