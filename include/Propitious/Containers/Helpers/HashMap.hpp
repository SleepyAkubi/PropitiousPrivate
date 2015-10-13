#ifndef PROPITIOUS_MEMORY_CONTAINERS_HELPERS_HASHMAP_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HELPERS_HASHMAP_HPP

#include <Propitious/Containers/HashMap.hpp>
#include <Propitious/Containers/Array.hpp>
#include <cstdlib>

namespace Propitious
{
	namespace Memory
	{

		namespace
		{
			using vol = Allocator::vol;

			struct FindResult
			{
				vol hashIndex;
				vol dataIndex;
				vol dataPreviousIndex;
			};
		}

		template <typename T>
		b8 has(const HashMap<T>& hashmap, typename HashMap<T>::Key key);

		template <typename T>
		const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key);
		template <typename T>
		const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& defaultValue);

		namespace MultiHashMap
		{
			template <typename T>
			const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key, Array<T>& items);

			template <typename T>
			vol count(const HashMap<T>& hashmap, typename HashMap<T>::Key key);

			template <typename T>
			void insert(HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& value);

			template <typename T>
			void remove(HashMap<T>& hashmap, const typename HashMap<T>::Entry* entry);

			template <typename T>
			void removeAll(HashMap<T>& hashmap, typename HashMap<T>::Key key);

			template <typename T>
			const typename HashMap<T>::Entry* begin(const HashMap<T>& hashmap);
			template <typename T>
			const typename HashMap<T>::Entry* end(const HashMap<T>& hashmap);

		}

		template <typename T>
		void set(HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& value);
		template <typename T>
		void remove(HashMap<T>& hashmap, typename HashMap<T>::Key key);

		template <typename T>
		void reserve(const HashMap<T>& hashmap, typename HashMap<T>::Key key, vol capacity);

		template <typename T>
		void clear(HashMap<T>& hashmap);

		template <typename T>
		HashMap<T>::HashMap(Allocator& a);

		namespace
		{
			template <typename T>
			void erase(HashMap<T>& hashmap, const FindResult& foundResult);
			template <typename T>
			vol addEntry(HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			void findAndErase(HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			FindResult find(const HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			FindResult find(const HashMap<T>& hashmap, const typename HashMap<T>::Entry* entry);
			template <typename T>
			vol findOrFail(const HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			vol make(HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			vol findOrMake(HashMap<T>& hashmap, typename HashMap<T>::Key key);
			template <typename T>
			bool full(HashMap<T>& hashmap);
			template <typename T>
			void rehash(HashMap<T>& hashmap, vol newCapacity);
			template <typename T>
			void grow(HashMap<T>& hashmap);
			template <typename T>
			const typename HashMap<T>::Entry* findFirst(const HashMap<T> hashmap, typename HashMap<T>::Key key);
			template <typename T>
			const typename HashMap<T>::Entry* findNext(const HashMap<T> hashmap, typename HashMap<T>::Entry* entry);

			template <typename T>
			inline void erase(HashMap<T>& hashmap, const FindResult& foundResult)
			{
				if (foundResult.dataPreviousIndex == EndOf::Hash)
					hashmap.hashes[foundResult.hashIndex] = hashmap.data[foundResult.dataIndex].next;
				else
					hashmap.data[foundResult.dataPreviousIndex].next = hashmap.data[foundResult.dataIndex].next;

				if (foundResult.dataIndex == length(hashmap.data) - 1)
				{
					popBack(hashmap.data);
					return;
				}

				hashmap.data[foundResult.dataIndex] = hashmap.data[length(hashmap.data) - 1];
				FindResult last = find(hashmap, hashmap.data[foundResult.dataIndex].key);

				if (last.dataPreviousIndex == EndOf::Hash)
					hashmap.hashes[last.hashIndex] = foundResult.dataIndex;
				else
					hashmap.data[last.dataIndex].next = foundResult.dataIndex;
			}

			template <typename T>
			inline vol addEntry(HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				HashMap<T>::Entry newEntry;
				newEntry.key = key;
				newEntry.next = EndOf::Hash;
				vol entryIndex = length(hashmap.data);
				pushBack(hashmap.data, newEntry);

				return entryIndex;
			}

			template <typename T>
			inline void findAndErase(HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				const FindResult fr = find(hashmap, key);
				if (fr.dataIndex != EndOf::Hash)
					erase(hashmap, fr);
			}

			template <typename T>
			inline FindResult find(const HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				FindResult fr;
				fr.hashIndex = EndOf::Hash;
				fr.dataIndex = EndOf::Hash;
				fr.dataPreviousIndex = EndOf::Hash;

				if (length(hashmap.hashes) == 0)
					return fr;

				fr.hashIndex = key % length(hashmap.hashes);
				fr.dataIndex = hashmap.hashes[fr.hashIndex];
				while (fr.dataIndex != EndOf::Hash)
				{
					if (hashmap.data[fr.dataIndex].key == key)
						return fr;

					fr.dataPreviousIndex = fr.dataIndex;
					fr.dataIndex = hashmap.data[fr.dataIndex].next;
				}

				return fr;
			}

			template <typename T>
			inline FindResult find(const HashMap<T>& hashmap, const typename HashMap<T>::Entry* entry)
			{
				FindResult fr;
				fr.hashIndex = EndOf::Hash;
				fr.dataIndex = EndOf::Hash;
				fr.dataPreviousIndex = EndOf::Hash;

				if (length(hashmap.hashes) == 0 || !e)
					return fr;

				fr.hashIndex = entry->key % length(hashmap.hashes);
				fr.dataIndex = hashmap.hashes[fr.hashIndex];
				while (fr.dataIndex != EndOf::Hash)
				{
					if (&hashmap.data[fr.dataIndex] == e)
						return fr;

					fr.dataPreviousIndex = fr.dataIndex;
					fr.dataIndex = hashmap.data[fr.dataIndex].next;
				}

				return fr;
			}


			template <typename T>
			inline vol make(HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				const FindResult fr = find(hashmap, key);
				const vol index = addEntry(hashmap, key);

				if (fr.dataPreviousIndex == EndOf::Hash)
					hashmap.hashes[fr.hashIndex] = index;
				else
					hashmap.data[fr.dataPreviousIndex].next = index;

				hashmap.data[index].next = fr.dataIndex;

				return index;
			}

			template <typename T>
			inline vol findOrFail(const HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				return find(hashmap, key).dataIndex;
			}

			template <typename T>
			inline vol findOrMake(HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				const FindResult fr = find(hashmap, key);
				if (fr.dataIndex != EndOf::Hash)
					return fr.dataIndex;

				vol index = addEntry(hashmap, key);
				if (fr.dataPreviousIndex == EndOf::Hash)
					hashmap.hashes[fr.hashIndex] = index;
				else
					hashmap.data[fr.dataPreviousIndex].next = index;

				return index;
			}

			template <typename T>
			inline bool full(HashMap<T>& hashmap)
			{
				return length(hashmap.data) >= 0.75f * length(hashmap.hashes);
			}

			template <typename T>
			inline void rehash(HashMap<T>& hashmap, vol newCapacity)
			{
				HashMap<T> newHashMap{ *hashmap.hashes.allocator };
				resize(newHashMap.hashes, newCapacity);
				const vol oldLength = length(hashmap.data);
				reserve(newHashMap.data, length(hashmap.data));

				for (vol i = 0; i < newCapacity; i++)
					newHashMap.hashes[i] = EndOf::Hash;

				for (vol i = 0; i < oldLength; i++)
				{
					auto& entry = hashmap.data[i];
					MultiHashMap::insert(newHashMap, entry.key, entry.value);
				}

				HashMap<T> empty(*hashmap.hashes.allocator);
				hashmap.~HashMap<T>();

				std::memcpy(&hashmap, &newHashMap, sizeof(HashMap<T>));
				std::memcpy(&newHashMap, &empty, sizeof(HashMap<T>));
			}

			template <typename T>
			inline void grow(HashMap<T>& hashmap)
			{
				const vol newCapacity = 2 * length(hashmap.data) + 2;
				rehash(hashmap, newCapacity);
			}

			template <typename T>
			const typename HashMap<T>::Entry* findFirst(const HashMap<T> hashmap, typename HashMap<T>::Key key)
			{
				const vol index = findOrFail(hashmap, key);
				if (index == EndOf::Hash)
					return nullptr;

				return &h.data[index];
			}
			template <typename T>
			const typename HashMap<T>::Entry* findNext(const HashMap<T> hashmap, typename HashMap<T>::Entry* entry)
			{
				if (!e)
					return nullptr;

				vol index = e->next;
				while (index != EndOf::Hash)
				{
					if (hashmap.data[index].key == e->key)
						return &h.data[index];
					index = hashmap.data[index].next;
				}

				return nullptr;
			}
		}

		template <typename T>
		inline b8 has(const HashMap<T>& hashmap, typename HashMap<T>::Key key)
		{
			return findOrFail(hashmap, key) != EndOf::Hash;
		}

		template <typename T>
		inline const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key)
		{
			const vol index = findOrFail(hashmap, key);
			assert(index != EndOf::Hash);
			return hashmap.data[index].value;
		}
		template <typename T>
		inline const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& defaultValue)
		{
			const vol index = findOrFail(hashmap, key);
			if (index == EndOf::Hash)
				return defaultValue;

			return hashmap.data[index].value;
		}

		template <typename T>
		void set(HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& value)
		{
			if (length(hashmap.hashes) == 0)
				grow(hashmap);

			const vol index = findOrMake(hashmap, key);
			hashmap.data[index].value = value;
			if (full(hashmap))
				grow(hashmap);
		}
		template <typename T>
		void remove(HashMap<T>& hashmap, typename HashMap<T>::Key key)
		{
			findAndErase(hashmap, key);
		}

		template <typename T>
		void reserve(const HashMap<T>& hashmap, typename HashMap<T>::Key key, vol capacity)
		{
			rehash(hashmap, capacity);

		}

		template <typename T>
		inline void clear(HashMap<T>& hashmap)
		{
			clear(hashmap.hashes);
			clear(hashmap.data);
		}

		template <typename T>
		HashMap<T>::HashMap(Allocator& a)
			: hashes(a)
			, data(a)
		{
		}

		namespace MultiHashMap
		{
			template <typename T>
			const T& get(const HashMap<T>& hashmap, typename HashMap<T>::Key key, Array<T>& items)
			{
				const HashMap<T>::Entry* entry = findFirst(hashmap, key);

				while (entry)
				{
					pushBack(items, e->value);
					e = findNext(hashmap, key);
				}
			}

			template <typename T>
			void removeAll(HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				while (has(hashmap, key))
					remove(h, key);
			}

			template <typename T>
			vol count(const HashMap<T>& hashmap, typename HashMap<T>::Key key)
			{
				vol count = 0;
				auto entry = findFirst(hashmap, key);
				while (entry)
				{
					c++;
					e = findNext(hashmap, entry);
				}

				return count;
			}

			template <typename T>
			void insert(HashMap<T>& hashmap, typename HashMap<T>::Key key, const T& value)
			{
				if (length(hashmap.hashes) == 0)
					grow(hashmap);

				const vol next = make(hashmap, key);
				hashmap.data[next].value = value;
				if (full(hashmap))
					grow(hashmap);
			}

			template <typename T>
			inline const typename HashMap<T>::Entry* begin(const HashMap<T>& hashmap)
			{
				return begin(hashmap.data);
			}

			template <typename T>
			void remove(HashMap<T>& hashmap, const typename HashMap<T>::Entry* entry)
			{
				const FindResult fr = find(hashmap, entry);
				if (fr.dataIndex != EndOf::Hash)
					erase(hashmap, fr);
			}

			template <typename T>
			inline const typename HashMap<T>::Entry* end(const HashMap<T>& hashmap)
			{
				return end(hashmap.data);
			}
		}
	}
}

#endif
