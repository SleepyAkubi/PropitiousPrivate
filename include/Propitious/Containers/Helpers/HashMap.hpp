#ifndef PROPITIOUS_CONTAINERS_HELPERS_HASHMAP_HPP
#define PROPITIOUS_CONTAINERS_HELPERS_HASHMAP_HPP

#include <Propitious/Containers/HashMap.hpp>
#include <Propitious/Containers/Array.hpp>
#include <cstdlib>

namespace Propitious
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
	}
}

#endif