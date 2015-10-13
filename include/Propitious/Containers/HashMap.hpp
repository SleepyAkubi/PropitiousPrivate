#ifndef PROPITIOUS_MEMORY_CONTAINERS_HASHMAP_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HASHMAP_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	namespace Memory
	{
		namespace EndOf
		{
			const vol Hash = EndOf::Vol;
		}

		namespace
		{
			using vol = Allocator::vol;
		}

		/**
		 This is a hash map (hash table):
		 ? Type: struct<typename T>
		 ? Notes:
			• Data structure that can map keys to values.
			• Template of the type of values you want to store in the data (Entry struct).
		*/
		template <typename T>
		struct HashMap
		{
			/**
			This is the type of key that will be used in the hash map (hash table):
			? Type: u64 (unsigned 64bit integer)
			*/
			using Key = u64;

			/**
			This is an entry to a hash map (hash table):
			? Type: struct<typename T> (where T is of the parent hash map (hash table)'s value)
			? Notes:
				• Template of the type of values.
				• Contains key of unsigned 64bit integer (or whatever Key is defined to as in the using directive).
				• Contains the id of the next entry.
			*/
			struct Entry
			{
				Key key;
				vol next;
				T value;
			};

			Array<vol>   hashes;
			Array<Entry> data;

			HashMap(Allocator& a = defaultAllocator());
		};
	}
}

#include <Propitious/Containers/Helpers/HashMap.hpp>

#endif
