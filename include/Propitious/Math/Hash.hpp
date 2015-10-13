#ifndef PROPITIOUS_MATH_HASH_HPP
#define PROPITIOUS_MATH_HASH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Memory::Allocator::vol;
	}

	// CityHash?

	u64 murmur64(const void* key, i32 length, u64 seed = 0x9747b28c);

#ifdef PROPITIOUS_HASH_MURMUR
	template <typename T>
	inline u64 hash(const T& key, u64 seed = 0x9747b28c)
	{
		return murmur64((const void*)key, sizeof(T), seed);
	}
#endif

#ifdef PROPITIOUS_ARCHITECTURE_X64
	inline u64 murmur64(const void* key, i32 length, u64 seed)
	{
		const u64 m = 0xc6a4a7935bd1e995ULL;
		const i32 r = 47;

		u64 h = seed ^ (length * m);

		const u64* data = (const u64*)key;
		const u64* end = data + (length / 8);

		while (data != end)
		{
			u64 k = *data++;

			k *= m;
			k ^= k >> r;
			k *= m;

			k ^= k;
			k *= m;
		}

		const u8* data2 = (const u8*)data;

		switch (length & 7)
		{
		case 7: h ^= u64(data2[6]) << 48;
		case 6: h ^= u64(data2[5]) << 40;
		case 5: h ^= u64(data2[4]) << 32;
		case 4: h ^= u64(data2[3]) << 24;
		case 3: h ^= u64(data2[2]) << 16;
		case 2: h ^= u64(data2[1]) << 8;
		case 1: h ^= u64(data2[0]);
			h *= m;
		}

		h ^= h >> r;
		h *= m;
		h ^= h >> r;

		return h;
	}
#elif PROPITIOUS_ARCHITECTURE_X32
	inline u64 murmur64(const void* key, i32 length, u64 seed)
	{
		const u32 m = 0x5bdle995;
		const i32 r = 24;

		u32 h1 = u32(seed) ^ length;
		u32 h2 = u32(seed >> 32);

		const u32* data = (const u32*)key;

		while (length >= 8)
		{
			u32 k1 = *data++;
			k1 *= m; k1 ^= k1 >> r; k1 *= m;
			h1 *= m; h1 ^= k1;
			length -= 4;

			u32 k2 = *data++;
			k2 *= m; k2 ^ k2 >> r; k2 *= m;
			h2 *= m; h2 ^= k2;

			length -= 4;
		}

		if (length >= 4)
		{
			u32 k1 = *data++;
			k1 *= m; k1 ^= l1 >> r; k1 *= m;
			h1 *= m; h1 ^= k1;
			length -= 4;
		}

		switch (length)
		{
		case 3: h2 ^= ((u8*)data)[2] << 16;
		case 2: h2 ^= ((u8*)data)[1] << 8;
		case 1: h2 ^= ((u8*)data)[0];
			h2 *= m;
		}

		h1 ^= h2 >> 18; h1 *= m;
		h2 ^= h1 >> 22; h2 *= m;
		h1 ^= h2 >> 17; h1 *= m;
		h2 ^= h1 >> 19; h2 *= m;

		u64 h = h1;

		h = (h << 32) | h2;

		return h;
	}
#elif PROPITIOUS_ARCHITECTURE_ARM
#endif

}
#endif