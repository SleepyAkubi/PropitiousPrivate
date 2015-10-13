#ifndef PROPITIOUS_MEMORY_CONTAINERS_HASHMAP_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HASHMAP_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	namespace EndOf
	{
		const vol Hash = Memory::EndOf::Vol;
	}

	namespace
	{
		using vol = Memory::Allocator::vol;
	}

	template <typename T>
	struct HashMap
	{
		using Key = u64;
		struct Entry
		{
			Key key;
			vol next;
			T value;
		};

		Array<vol>   hashes;
		Array<Entry> data;

		HashMap(Memory::Allocator& a = defaultAllocator());
	};
}

#include <Propitious/Containers/Helpers/HashMap.hpp>

#endif
