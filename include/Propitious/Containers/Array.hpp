#ifndef PROPITIOUS_MEMORY_CONTAINERS_ARRAY_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_ARRAY_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>

namespace Propitious
{
	namespace Memory
	{
		namespace
		{
			using vol = Allocator::vol;
		}

		template <typename T>
		struct Array
		{
			Array(Allocator& allocator = defaultAllocator());

			~Array();

			Array(const Array& other);

			Array& Array::operator=(const Array& other);

			T& operator[](vol index)
			{
				return data[index];
			}

			const T& operator[](vol index) const
			{
				return data[index];
			}

			Allocator* allocator;
			vol length;
			vol capacity;
			T* data;
		};
	}
}

#include <Propitious/Containers/Helpers/Array.hpp>

#endif
