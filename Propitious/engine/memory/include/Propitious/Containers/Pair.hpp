#ifndef PROPITIOUS_MEMORY_CONTAINERS_PAIR_HPP
#define PROPITIOUS_MEMORY_CONTAINERS_PAIR_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Common.hpp>

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

		template <typename A, typename B>
		struct Pair
		{
			A first;
			B second;
		};
	}
}

#endif