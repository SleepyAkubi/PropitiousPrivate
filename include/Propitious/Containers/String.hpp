#ifndef PROPITIOUS_CONTAINERS_STRING_HPP
#define PROPITIOUS_CONTAINERS_STRING_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT String
	{
		Array<a8> data;

		String(Allocator& allocator = defaultAllocator());
		String(a8 character, Allocator& allocator = defaultAllocator());
		String(const a8* characterArray, Allocator& allocator = defaultAllocator());
		String(const String& string);

		String& operator=(const String& string);
		String& operator=(const a8* characterArray);
		String& operator=(const a8 character);

		~String() = default;

		inline a8& operator[](usize index) { return data[index]; }
		inline const a8& operator[](usize index) const { return data[index]; }
	};
}

#include <Propitious/Containers/Helpers/String.hpp>

#endif