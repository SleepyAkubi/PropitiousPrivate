#include <Propitious/Memory/Memory.hpp>

#include <mutex>
#include <cstdlib>

namespace Propitious
{
	namespace {

		using vol = Allocator::vol;

		struct MemoryHeader
		{
			static const Allocator::vol PaddingValue = (vol)(-1);

			vol size;
		};
	}

	class HeapAllocator : public Allocator
	{
	public:
		HeapAllocator() : totalAllocatedSpace(0), allocationCount(0) {}
		~HeapAllocator() {}

		virtual void* allocate(vol size, vol align = defaultAlignment)
		{
			mutex.lock();
			const vol total = size + align + sizeof(MemoryHeader);

			MemoryHeader* header = (MemoryHeader*)std::malloc(total);
			header->size = total;

			void* ptr = alignForward(header + 1, align);

			pad(header, ptr);

			totalAllocatedSpace += total;
			allocationCount++;

			mutex.unlock();

			return ptr;
		}
		virtual void deallocate(void* pointer)
		{
			if (!pointer)
				return;
			mutex.lock();

			MemoryHeader* head = header(pointer);

			totalAllocatedSpace -= head->size;
			allocationCount--;

			free(head);
			mutex.unlock();

		}
		virtual vol allocatedSize(void* pointer)
		{
			return header(pointer)->size;
		}

		inline void pad(MemoryHeader* header, void* data)
		{
			vol* ptr = (vol*)(header + 1);

			while (ptr != data)
				*ptr++ = MemoryHeader::PaddingValue;
		}

		inline MemoryHeader* header(const void* data)
		{
			const vol* ptr = (vol*)data;
			ptr--;

			while (*ptr == MemoryHeader::PaddingValue)
				ptr--;

			return (MemoryHeader*)ptr;
		}

		vol totalAllocatedSpace;
		vol allocationCount;
		std::mutex mutex;
	};

	namespace
	{
		struct MemoryImplementation
		{
			const vol allocatorMemory = sizeof(HeapAllocator);
			u8 buffer[sizeof(HeapAllocator)];

			HeapAllocator* defaultAllocator = nullptr;
		};

		MemoryImplementation* memimp = new MemoryImplementation;
	}

	Allocator& defaultAllocator()
	{
		return *memimp->defaultAllocator;
	}

	namespace Implementation
	{
		void initialiseMemory()
		{
			u8* bufferPointer = memimp->buffer;
			memimp->defaultAllocator = new (bufferPointer) HeapAllocator{};
		}

		void shutdownMemory()
		{
			if (memimp)
			{
				memimp->defaultAllocator->~HeapAllocator();
				delete memimp;
			}
		}
	}
}