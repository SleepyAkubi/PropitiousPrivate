#ifndef PROPITIOUS_MEMORY_ALLOCATOR_HPP
#define PROPITIOUS_MEMORY_ALLOCATOR_HPP

#include <Propitious/Common.hpp>

#include <new>
#include <utility>

namespace Propitious
{
	namespace Memory
	{
		class propexp Allocator : private NonCopyable
		{
		public:
#ifdef PROPITIOUS_ARCHITECTURE_X64
			using vol = u32;
#elif PROPITIOUS_ARCHITECTURE_X32
			using vol = usize;
#else
#pragma message("Unknown Architecture! Memory size may be wrong!")
			using vol = usize;
#endif

			static const vol defaultAlignment = 4;
			static const vol notTracked = (vol)(-1);

			Allocator() {}
			virtual ~Allocator() {}

			virtual void* allocate(vol size, vol alignment = defaultAlignment) = 0;
			virtual void  deallocate(void* pointer) = 0;
			virtual vol   allocatedSize(void* pointer) = 0;

			template <typename T, typename... Args>
			T* spawn(Args&&... args)
			{
				return new (allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args...));
			}

			template <typename T>
			void murder(T* ptr)
			{
				if (ptr)
				{
					ptr->~T();
					deallocate(ptr);
				}
			}
		};

		namespace EndOf
		{
			const Allocator::vol Vol = (Allocator::vol)(-1);
		}

		propexp Allocator& defaultAllocator();
	}

	void* operator new(Propitious::usize size) throw(std::bad_alloc)
	{
		Propitious::Memory::Allocator& allocator = Propitious::Memory::defaultAllocator();
		return allocator.allocate(size);
	}

	void operator delete(void* size) throw()
	{
		Propitious::Memory::Allocator& allocator = Propitious::Memory::defaultAllocator();
		return allocator.deallocate(size);
	}
}

#endif
