#ifndef PROPITIOUS_MEMORY_ALLOCATOR_HPP
#define PROPITIOUS_MEMORY_ALLOCATOR_HPP

#include <Propitious/Common.hpp>

#include <new>
#include <utility>

namespace Propitious
{
	class propexp Allocator : private NonCopyable
	{
	public:
		using vol = usize;

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

#ifndef PROPITIOUS_DONT_MANAGE_MEMORY

inline void* operator new(Propitious::usize size)
{
	Propitious::Allocator& allocator = Propitious::defaultAllocator();
	return allocator.allocate((Propitious::Allocator::vol) size);
}

inline void operator delete(void* size)
{
	Propitious::Allocator& allocator = Propitious::defaultAllocator();
	return allocator.deallocate(size);
}

#endif

#endif
