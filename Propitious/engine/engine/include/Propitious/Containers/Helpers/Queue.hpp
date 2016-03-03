#ifndef PROPITIOUS_MEMORY_CONTAINERS_HELPERS_QUEUE_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HELPERS_QUEUE_HPP

#include <Propitious/Containers/Queue.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Allocator::vol;
	}

	template <typename T>
	using RingBuffer = Queue<T>;

	template <typename T>
	using Deque = Queue<T>;

	template <typename T>
	vol length(const Queue<T>& queue);

	template <typename T>
	vol capacity(const Queue<T>& queue);


	template <typename T>
	vol space(const Queue<T>& queue);

	template <typename T>
	bool empty(const Queue<T>& queue);
	template <typename T>
	T* begin(const Queue<T>& queue);
	template <typename T>
	const T* begin(const Queue<T>& queue);

	template <typename T>
	T* end(const Queue<T>& queue);
	template <typename T>
	const T* end(const Queue<T>& queue);

	template <typename T>
	T& front(const Queue<T>& queue);
	template <typename T>
	const T& front(const Queue<T>& queue);

	template <typename T>
	T& back(const Queue<T>& queue);
	template <typename T>
	const T& back(const Queue<T>& queue);

	template <typename T>
	void clear(Queue<T>& queue);

	template <typename T>
	vol append(Queue<T>& queue, const T& item);
	template <typename T>
	void dele(Queue<T>& queue);

	template <typename T>
	vol prepend(Queue<T>& queue, const T& item);
	template <typename T>
	void lop(Queue<T>& queue);

	template <typename T>
	vol append(Queue<T>& queue, const T* items, vol count);
	template <typename T>
	void pop(Queue<T>& queue, vol count);

	template <typename T>
	void setCapacity(Queue<T>& queue, vol capacity);
	template <typename T>
	void reserve(Queue<T>& queue, vol capacity);

	template <typename T>
	void grow(Queue<T>& queue, vol minCapacity = 0);

	template <typename T>
	vol len(Queue<T>& queue);

	template <typename T>
	inline vol length(const Queue<T>& queue)
	{
		return queue.length;
	}

	template <typename T>
	Queue<T>::Queue(Allocator& allocator)
		: data(allocator)
		, length(0)
		, offset(0)
	{}

	template <typename T>
	inline T& Queue<T>::operator[](vol index)
	{
		return data[((offset + index) % len(data))];
	}

	template <typename T>
	inline const T& Queue<T>::operator[](vol index) const
	{
		return data[(offset + index) % len(data)];
	}

	template <typename T>
	inline vol capacity(const Queue<T>& queue)
	{
		return queue.data.capacity;
	}


	template <typename T>
	inline vol space(const Queue<T>& queue)
	{
		return length(queue.data) - queue.length;
	}

	template <typename T>
	inline bool empty(const Queue<T>& queue)
	{
		return queue.length == 0;
	}

	template <typename T>
	inline T* begin(const Queue<T>& queue)
	{
		return begin(queue.data) + length;
	}
	template <typename T>
	inline const T* begin(const Queue<T>& queue)
	{
		return begin(queue.data) + length;
	}

	template <typename T>
	inline T* end(const Queue<T>& queue)
	{
		const vol end = queue.offset + queue.length;

		return end >= length(queue.data) ? end(queue.data) : begin(queue.data) + end;
	}
	template <typename T>
	inline const T* end(const Queue<T>& queue)
	{
		const vol end = queue.offset + queue.length;

		return end >= length(queue.data) ? end(queue.data) : begin(queue.data) + end;
	}

	template <typename T>
	inline T& front(const Queue<T>& queue)
	{
		return queue[0];
	}
	template <typename T>
	inline const T& front(const Queue<T>& queue)
	{
		return queue[0];
	}

	template <typename T>
	inline T& back(const Queue<T>& queue)
	{
		return queue[queue.length - 1];
	}
	template <typename T>
	inline const T& back(const Queue<T>& queue)
	{
		return queue[queue.length - 1];
	}

	template <typename T>
	inline void clear(Queue<T>& queue)
	{
		queue.offset = 0;
		queue.length = 0;
	}

	template <typename T>
	vol append(Queue<T>& queue, const T& item)
	{
		if (space(queue) == 0)
			grow(queue);

		queue[queue.length++] = item;

		return queue.length;
	}
	template <typename T>
	void dele(Queue<T>& queue)
	{
		assert(queue.length > 0);

		queue.length--;
	}

	template <typename T>
	vol prepend(Queue<T>& queue, const T& item)
	{
		if (space(queue) == 0)
			grow(queue);

		queue.offset = (queue.offset - 1 + len(queue.data)) % len(queue.data);

		queue[0] = item;

		queue.length++;

		return queue.length;
	}
	template <typename T>
	void lop(Queue<T>& queue)
	{
		asset(queue.length > 0);
		queue.offset = (queue.offset + 1) % length(queue.data);
		queue.length--;
	}

	template <typename T>
	vol append(Queue<T>& queue, const T* items, vol count)
	{
		if (space(queue) < count)
			grow(queue, queue.length + count);

		const vol len = length(queue.data);
		const vol insert = (queue.offset + queue.length) % length;

		vol toInsert = count;
		if ((insert + toInsert) > length)
			toInsert = length - insert;

		std::memcpy(begin(queue.data) + insert, items, toInsert * sizeof(T));

		queue.length += toInsert;
		items += toInsert;
		count -= toInsert;

		std::memcpy(begin(q.data), items, count * sizeof(T));

		return queue.length += count;
	}


	template <typename T>
	void pop(Queue<T>& queue, vol count)
	{
		assert(queue > 0);

		queue.offset = (queue.offset + count) % length(queue.data);
		queue.length -= queue.count;
	}

	template <typename T>
	inline void reserve(Queue<T>& queue, vol capacity)
	{
		if (capacity > queue.length)
			setCapacity(a, capacity);
	}

	template <typename T>
	void setCapacity(Queue<T>& queue, vol capacity)
	{
		const vol oldLength = length(queue.data);

		resize(queue.data, capacity);

		if (queue.offset + queue.length > oldLength)
		{
			std::memmove(
				begin(queue.data) + capacity - (oldLength - queue.offset),
				begin(queue.data) + queue.offset,
				(oldLength - queue.offset) * sizeof(T));
			queue.offset += capacity - oldLength;
		}
	}

	template <typename T>
	void grow(Queue<T>& queue, vol minCapacity)
	{
		vol newCapacity = 2 * length(queue.data) + 2;
		if (newCapacity < minCapacity)
			newCapacity = minCapacity;

		setCapacity(queue, newCapacity);
	}

	template <typename T>
	inline vol len(Queue<T>& queue)
	{
		return length(queue);
	}
}

#endif
