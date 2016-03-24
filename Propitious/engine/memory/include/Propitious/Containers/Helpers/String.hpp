#ifndef PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP
#define PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP

#include <Propitious/Memory/Common.hpp>

#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	PROPITIOUS_MEMORY_EXPORT usize length(const String& string);
	PROPITIOUS_MEMORY_EXPORT usize capacity(const String& string);

	PROPITIOUS_MEMORY_EXPORT usize append(String& string, a8 character);
	PROPITIOUS_MEMORY_EXPORT usize append(String& string, const a8* characterArray);
	PROPITIOUS_MEMORY_EXPORT usize append(String& string1, const String& string2);

	PROPITIOUS_MEMORY_EXPORT a8* begin(String& string);
	PROPITIOUS_MEMORY_EXPORT const a8* begin(const String& string);
	PROPITIOUS_MEMORY_EXPORT a8* end(String& string);
	PROPITIOUS_MEMORY_EXPORT const a8* end(const String& string);

	PROPITIOUS_MEMORY_EXPORT a8& front(String& string);
	PROPITIOUS_MEMORY_EXPORT const a8& front(const String& string);
	PROPITIOUS_MEMORY_EXPORT a8& back(String& string);
	PROPITIOUS_MEMORY_EXPORT const a8& back(const String& string);

	PROPITIOUS_MEMORY_EXPORT const a8* cString(const String& string);
	//PROPITIOUS_MEMORY_EXPORT const a8* wcString(const String& string);

	PROPITIOUS_MEMORY_EXPORT void clear(String& string);

	PROPITIOUS_MEMORY_EXPORT void trim(String& string);

	PROPITIOUS_MEMORY_EXPORT usize find(const String& string, const String& substring);
	PROPITIOUS_MEMORY_EXPORT usize findLast(const String& string, const String& substring);

	PROPITIOUS_MEMORY_EXPORT Array<const a8*> split(const String& string, a8 delim);

	PROPITIOUS_MEMORY_EXPORT void resize(String& string, usize length);

	PROPITIOUS_MEMORY_EXPORT void reserve(String& string, usize capacity);

	PROPITIOUS_MEMORY_EXPORT String substring(const String& s, usize begin, usize end);

	PROPITIOUS_MEMORY_EXPORT String operator+(const String& lhs, const String& rhs);

	PROPITIOUS_MEMORY_EXPORT String operator+(const String& lhs, const a8* rhs);
	PROPITIOUS_MEMORY_EXPORT String operator+(const a8* lhs, const String& rhs);

	PROPITIOUS_MEMORY_EXPORT String operator+(const String& lhs, a8 rhs);
	PROPITIOUS_MEMORY_EXPORT String operator+(a8 lhs, const String& rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator==(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator==(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator==(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator!=(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator!=(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator!=(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator<(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator<(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator<(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator<=(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator<=(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator<=(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator>(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator>(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator>(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT b8 operator>=(const String& lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator>=(const a8* lhs, const String& rhs);
	PROPITIOUS_MEMORY_EXPORT b8 operator>=(const String& lhs, const a8* rhs);

	PROPITIOUS_MEMORY_EXPORT std::ostream& operator<<(std::ostream& os, const String& string);
	PROPITIOUS_MEMORY_EXPORT std::istream& operator>>(std::istream& is, String& string);

	PROPITIOUS_MEMORY_EXPORT std::istream& getline(std::istream& is, String& string);

	//PROPITIOUS_MEMORY_EXPORT const a8* widen(const a8* string);
	//PROPITIOUS_MEMORY_EXPORT const a8* unwiden(const a8* string);
}

#endif