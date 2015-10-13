#ifndef PROPITIOUS_MEMORY_CONTAINERS_QUEUE_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_QUEUE_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
		namespace
		{
			using vol = Memory::Allocator::vol;
		}

		template <typename T>
		struct Queue
		{
			Queue(Memory::Allocator& a = defaultAllocator());

			T& operator[](vol index);
			const T& operator[](vol index) const;

			Array<T> data;
			vol length;
			vol offset;
		};
}

#include <Propitious\Containers\Helpers\Queue.hpp>

#endif