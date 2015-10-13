#include <Propitious/Common.hpp>
#include <Propitious/Containers/Helpers/Array.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Memory::Allocator::vol;
	}

	template <typename T>
	inline Array<T>::Array(Memory::Allocator& allocator)
		: allocator(&allocator)
		, length(0)
		, capacity(0)
		, data(nullptr)
	{}

	template <typename T>
	inline Array<T>::~Array()
	{
		allocator->deallocate(data);
	}

	template <typename T>
	Array<T>::Array(const Array<T>& other)
		: allocator(other.allocator)
		, length(0)
		, capacity(0)
		, data(nullptr)
	{
		const vol numberOfOtherElements = other.length;
		setCapacity(*this, numberOfOtherElements);
		std::memcpy(data, other.data, numberOfOtherElements * sizeof(T));
		length = numberOfOtherElements;
	}

	template <typename T>
	inline Array<T>& Array<T>::operator=(const Array& other)
	{
		const vol numberOfOtherElements = other.length;
		resize(*this, numberOfOtherElements);
		std::memcpy(data, other.data, numberOfOtherElements * sizeof(T));
		return *this;
	}

	template <typename T>
	vol pushBack(Array<T>& array, const T& item)
	{
		if (array.length == array.capacity)
			grow(array);

		array.data[array.length++] = item;

		return array.length;
	}
	template <typename T>
	void popBack(Array<T>& array)
	{
		assert(array.length > 0);

		array.length--;
	}

	template <typename T, typename... Args>
	vol emplaceBack(Array<T>& array, const T& item, Args&&... args)
	{
		item(std::forward<Args>(args)...);
		pushBack(array, item);
	}

	template <typename T>
	vol length(const Array<T>& array)
	{
		return array.length;
	}

	template <typename T>
	vol len(const Array<T>& array)
	{
		return length(array);
	}

	template <typename T>
	inline vol capacity(const Array<T>& array)
	{
		return array.capacity;
	}

	template <typename T>
	inline bool empty(const Array<T>& array)
	{
		return array.length == 0;
	}

	template <typename T>
	inline T* begin(Array<T>& array)
	{
		return array.data;
	}
	template <typename T>
	inline const T* begin(const Array<T>& array)
	{
		return array.data;
	}

	template <typename T>
	inline T* end(Array<T>& array)
	{
		return array.data + array.length;
	}
	template <typename T>
	inline const T* end(const Array<T>& array)
	{
		return array.data + array.length;
	}

	template <typename T>
	inline T& front(const Array<T>& array)
	{
		return array.data[0];
	}
	template <typename T>
	inline const T& front(const Array<T>& array)
	{
		return array.data[0];
	}

	template <typename T>
	inline T& back(const Array<T>& array)
	{
		return array.data[array.length - 1];
	}
	template <typename T>
	inline const T& back(const Array<T>& array)
	{
		return array.data[array.length - 1];
	}

	template <typename T>
	inline void clear(Array<T>& array)
	{
		resize(array, 0);
	}

	template <typename T>
	inline void trim(Array<T>& array)
	{
		setCapacity(array, array.length);
	}

	template <typename T>
	vol push(Array<T>& array, const T* items, vol count)
	{
		vol fullSize = array.length + count;

		if (array.capacity <= fullSize)
			grow(array, fullSize)

			std::memcpy(&array.data[array.length], items, count * sizeof(T));
		array.length += count;

		return a.length;
	}

	template <typename T>
	void resize(Array<T>& array, vol length)
	{
		if (length > array.capacity)
			grow(array, length);
		array.length = length;
	}

	template <typename T>
	void setCapacity(Array<T>& array, vol capacity)
	{
		if (capacity == array.capacity)
			return;

		if (capacity < array.length)
			resize(array, capacity);

		T* data = nullptr;
		data = (T*)array.allocator->allocate(capacity * sizeof(T), alignof(T));
		std::memcpy(data, array.data, array.length * sizeof(T));
		array.allocator->deallocate(array.data);
		array.data = data;
		array.capacity = capacity;
	}

	template <typename T>
	inline void reserve(Array<T>& array, vol capacity)
	{
		if (capacity > array.capacity)
			setCapacity(array, capacity);
	}

	template <typename T>
	void grow(Array<T>& array, vol minCapacity)
	{
		vol capacity = 2 * array.capacity + 2;
		if (capacity < minCapacity)
			capacity = minCapacity;

		setCapacity(array, capacity);
	}
}