#ifndef PROPITIOUS_MEMORY_ALLOCATORS_TEMPALLOCATOR_HPP
#define PROPITIOUS_MEMORY_ALLOCATORS_TEMPALLOCATOR_HPP

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

		template <vol Size>
		class TempAllocator : public Allocator
		{
		public:
			TempAllocator(Allocator& backing = defaultAllocator());
			~TempAllocator();

			void* allocate(vol size, vol alignment = defaultAlignment);
			void  deallocate(void* pointer) {}
			vol   allocatedSize(void* pointer) { return notTracked; }

			Allocator& backing;
			u8 buffer[Size];

			u8* begin;
			u8* end;
			u8* current;

			vol chunkSize;
		};

		template <vol Size>
		inline TempAllocator<Size>::TempAllocator(Allocator& backing)
			: backing(backing)
			, chunkSize(4 * 1024 /* 4kb */)
		{
			current = begin = &buffer[0];
			end = begin + Size;
			*(void**)begin = nullptr;
			current += sizeof(void*);
		}

		template <vol Size>
		inline TempAllocator<Size>::~TempAllocator()
		{
			void* pointer = *(void**)buffer;
			while (pointer)
			{
				void* nextPtr = *(void**)pointer;
				backing.deallocate(pointer);
				pointer = nextPtr;
			}
		}

		template <vol Size>
		inline void* TempAllocator<Size>::allocate(vol size, vol alignment = defaultAlignment)
		{
			current = (u8*)alignForward(current, alignment);
			if (size > vol(end - current))
			{
				vol toAllocate = sizeof(void*) + size + alignment;

				if (toAllocate < chunkSize)
					toAllocate = chunkSize;

				chunkSize *= 2;

				void* pointer = backing.allocate(toAllocate);
				*(void**)begin = pointer;
				current = begin = (u8*)pointer;
				end = begin + toAllocate;

				*(void**)begin = nullptr;
				current += sizeof(void*);
				current = (u8*)alignForward(current, alignment);
			}

			void* result = current;
			current += size;

			return result;
		}
	}
}

#endif
