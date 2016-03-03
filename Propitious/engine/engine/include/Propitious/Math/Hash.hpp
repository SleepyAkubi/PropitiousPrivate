#ifndef PROPITIOUS_MATH_HASH_HPP
#define PROPITIOUS_MATH_HASH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{

	// CityHash?

	u64 murmur64(const void* key, i32 length, u64 seed = 0x9747b28c);

#ifdef PROPITIOUS_HASH_MURMUR
	template <typename T>
	inline u64 hash(const T& key, u64 seed = 0x9747b28c)
	{
		return murmur64((const void*)key, sizeof(T), seed);
	}
#endif

	inline u64 murmur64(const void* key, i32 length, u64 seed);

}
#endif