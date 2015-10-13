#ifndef PROPITIOUS_MEMORY_CONTAINERS_HELPERS_QUEUE_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_HELPERS_QUEUE_HPP

#include <Propitious/Containers/Queue.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Memory::Allocator::vol;
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
	vol pushBack(Queue<T>& queue, const T& item);
	template <typename T>
	void popBack(Queue<T>& queue);

	template <typename T>
	vol pushFront(Queue<T>& queue, const T& item);
	template <typename T>
	void popFront(Queue<T>& queue);

	template <typename T>
	vol push(Queue<T>& queue, const T* items, vol count);
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
}

#endif
