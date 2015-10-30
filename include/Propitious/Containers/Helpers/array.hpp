#ifndef PROPITIOUS_MEMORY_CONTAINERS_HELPERS_ARRAY_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HELPERS_ARRAY_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Allocator::vol;
	}

	template <typename T>
	inline Array<T>::Array(Allocator& allocator);

	template <typename T>
	inline Array<T>::~Array();

	template <typename T>
	Array<T>::Array(const Array<T>& other);

	template <typename T>
	inline Array<T>& Array<T>::operator=(const Array& other);

	template <typename T>
	vol pushBack(Array<T>& array, const T& item);
	template <typename T>
	void popBack(Array<T>& array);

	template <typename T, typename... Args>
	vol emplaceBack(Array<T>& array, const T& item, Args&&... args);

	template <typename T>
	vol length(const Array<T>& array);

	template <typename T>
	vol len(const Array<T>& array);

	template <typename T>
	inline vol capacity(const Array<T>& array);

	template <typename T>
	inline bool empty(const Array<T>& array);

	template <typename T>
	inline T* begin(Array<T>& array);
	template <typename T>
	inline const T* begin(const Array<T>& array);

	template <typename T>
	inline T* end(Array<T>& array);
	template <typename T>
	inline const T* end(const Array<T>& array);

	template <typename T>
	inline T& front(const Array<T>& array);
	template <typename T>
	inline const T& front(const Array<T>& array);

	template <typename T>
	inline T& back(const Array<T>& array);
	template <typename T>
	inline const T& back(const Array<T>& array);

	template <typename T>
	inline void clear(Array<T>& array);

	template <typename T>
	inline void trim(Array<T>& array);

	template <typename T>
	vol push(Array<T>& array, const T* items, vol count);

	template <typename T>
	void resize(Array<T>& array, vol length);

	template <typename T>
	void setCapacity(Array<T>& array, vol capacity);

	template <typename T>
	inline void reserve(Array<T>& array, vol capacity);

	template <typename T>
	void grow(Array<T>& array, vol minCapacity = 0);
}

#endif
