#ifndef PROPITIOUS_TYPES_HPP
#define PROPITIOUS_TYPES_HPP

#include <cstdint>
#include <cstddef>
#include <inttypes.h>

namespace Propitious
{
	using i8  = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using u8  = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using f32 = float;
	using f64 = double;

	using usize = std::size_t;

	using iptr = std::intptr_t;
	using uptr = std::uintptr_t;

	using b8 = bool;
	using b32 = i32;
}

#endif