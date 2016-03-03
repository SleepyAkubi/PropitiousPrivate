#ifndef PROPITIOUS_CONTAINERS_STRING_HPP
#define PROPITIOUS_CONTAINERS_STRING_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Containers/Array.hpp>

namespace Propitious
{
	namespace EndOf
	{
		usize String = (usize)-1;
	}
	struct PROPITIOUS_EXPORT String
	{
		Array<wchar> data;

		String(Allocator& allocator = defaultAllocator());
		String(wchar character, Allocator& allocator = defaultAllocator());
		String(const wchar* characterArray, Allocator& allocator = defaultAllocator());
		String(const a8* characterArray, Allocator& allocator = defaultAllocator());
		String(const String& string);

		String& operator=(const String& string);
		String& operator=(const wchar* characterArray);
		String& operator=(const wchar character);

		~String() = default;

		inline wchar& operator[](usize index) { return data[index]; }
		inline const wchar& operator[](usize index) const { return data[index]; }
	};
}

#include <Propitious/Containers/Helpers/String.hpp>

#endif