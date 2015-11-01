#ifndef PROPITIOUS_COMMON_TYPES_HPP
#define PROPITIOUS_COMMON_TYPES_HPP

#include <Propitious/Common/Architectures.hpp>

namespace Propitious
{
	// Unfortunately char can be signed/unsigned per platform/compiler so we need *another* type. Seems silly to me.
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

#ifdef PROPITIOUS_COMPILER_CLANG
	using i128 = signed __int128;
	using u128 = unsigned __int128;
#else
	using i128 = i64;
	using u128 = u64;
#endif

#if !PROPITIOUS_MAXINT_BITS
#elif PROPITIOUS_MAXINT_BITS == 64
	using usize = u64;
	using isize = i64;
#elif PROPITIOUS_MAXINT_BITS == 32
	using usize = u32;
	using isize = i32;
#elif PROPITIOUS_MAXINT_BITS == 16
	using usize = u16;
	using isize = i16;
#elif PROPITIOUS_MAXINT_BITS == 8
	using usize = u8;
	using isize = i8;
#endif

	using iptr = isize;
	using uptr = usize;

	using b8 = bool;
}

#endif