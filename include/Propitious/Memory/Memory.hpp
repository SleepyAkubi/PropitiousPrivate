#ifndef PROPITIOUS_MEMORY_MEMORY_HPP
#define PROPITIOUS_MEMORY_MEMORY_HPP

#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{
	namespace
	{
		using vol = Allocator::vol;
	}

	PROPITIOUS_EXPORT Allocator& defaultAllocator();

	namespace Implementation
	{
		PROPITIOUS_EXPORT void initialiseMemory();
		PROPITIOUS_EXPORT void shutdownMemory();
	}

	inline void* alignForward(void* pointer, Allocator::vol alignment)
	{
		uptr castedPointer = (uptr)pointer;
		const vol alignmentModulus = castedPointer % alignment;
		if (alignmentModulus)
			castedPointer += (uptr)(alignment - alignmentModulus);
		return (void*)castedPointer;
	}
}

#endif