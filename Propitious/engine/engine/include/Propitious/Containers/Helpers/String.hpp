#ifndef PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP
#define PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP

#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	PROPITIOUS_EXPORT usize length(const String& string);
	PROPITIOUS_EXPORT usize capacity(const String& string);

	PROPITIOUS_EXPORT usize append(String& string, wchar character);
	PROPITIOUS_EXPORT usize append(String& string, const wchar* characterArray);
	PROPITIOUS_EXPORT usize append(String& string1, const String& string2);

	PROPITIOUS_EXPORT wchar* begin(String& string);
	PROPITIOUS_EXPORT const wchar* begin(const String& string);
	PROPITIOUS_EXPORT wchar* end(String& string);
	PROPITIOUS_EXPORT const wchar* end(const String& string);

	PROPITIOUS_EXPORT wchar& front(String& string);
	PROPITIOUS_EXPORT const wchar& front(const String& string);
	PROPITIOUS_EXPORT wchar& back(String& string);
	PROPITIOUS_EXPORT const wchar& back(const String& string);

	PROPITIOUS_EXPORT const wchar* cString(const String& string);

	PROPITIOUS_EXPORT void clear(String& string);

	PROPITIOUS_EXPORT void trim(String& string);

	PROPITIOUS_EXPORT usize find(const String& string, const String& substring);
	PROPITIOUS_EXPORT usize findLast(const String& string, const String& substring);

	PROPITIOUS_EXPORT Array<const wchar*> split(const String& string, wchar delim);

	PROPITIOUS_EXPORT void resize(String& string, usize length);

	PROPITIOUS_EXPORT void reserve(String& string, usize capacity);

	PROPITIOUS_EXPORT String substring(const String& s, usize begin, usize end);

	PROPITIOUS_EXPORT String operator+(const String& lhs, const String& rhs);

	PROPITIOUS_EXPORT String operator+(const String& lhs, const wchar* rhs);
	PROPITIOUS_EXPORT String operator+(const wchar* lhs, const String& rhs);

	PROPITIOUS_EXPORT String operator+(const String& lhs, wchar rhs);
	PROPITIOUS_EXPORT String operator+(wchar lhs, const String& rhs);

	PROPITIOUS_EXPORT b8 operator==(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator==(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator==(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT b8 operator!=(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator!=(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator!=(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT b8 operator<(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator<(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator<(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT b8 operator<=(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator<=(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator<=(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT b8 operator>(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator>(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator>(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT b8 operator>=(const String& lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator>=(const wchar* lhs, const String& rhs);
	PROPITIOUS_EXPORT b8 operator>=(const String& lhs, const wchar* rhs);

	PROPITIOUS_EXPORT std::ostream& operator<<(std::ostream& os, const String& string);
	PROPITIOUS_EXPORT std::istream& operator>>(std::istream& is, String& string);

	PROPITIOUS_EXPORT std::istream& getline(std::istream& is, String& string);

	PROPITIOUS_EXPORT const wchar* widenString(const a8* string);
	PROPITIOUS_EXPORT const a8* unwiden(const wchar* string);
}

#endif