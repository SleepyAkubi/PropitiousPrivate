/*#ifndef PROPITIOUS_MEMORY_CONTAINERS_SET_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_SET_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	namespace Memory
	{
		namespace
		{
			using vol = Allocator::vol;
		}

		template <typename T>
		struct Data
		{
			T data;
		};

		template <typename... Args>
		struct Set
		{
			Array<Data*> array;

		};
	}
}

#endif*/