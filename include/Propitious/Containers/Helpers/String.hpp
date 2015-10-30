#ifndef PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP
#define PROPITIOUS_CONTAINERS_HELPERS_STRING_HPP

#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	usize length(const String& string);
	usize capacity(const String& string);

	usize append(String& string, a8 character);
	usize append(String& string, const a8* characterArray);
	usize append(String& string1, const String& string2);

	a8* begin(String& string);
	const a8* begin(const String& string);
	a8* end(String& string);
	const a8* end(const String& string);

	a8& front(String& string);
	const a8& front(const String& string);
	a8& back(String& string);
	const a8& back(const String& string);

	const a8* cString(const String& string);

	void clear(String& string);

	void trim(String& string);

	void resize(String& string, usize length);

	void reserve(String& string, usize capacity);

	String substring(const String& s, usize begin, usize end);

	String operator+(const String& lhs, const String& rhs);

	String operator+(const String& lhs, const a8* rhs);
	String operator+(const a8* lhs, const String& rhs);

	String operator+(const String& lhs, a8 rhs);
	String operator+(a8 lhs, const String& rhs);

	b8 operator==(const String& lhs, const String& rhs);
	b8 operator==(const a8* lhs, const String& rhs);
	b8 operator==(const String& lhs, const a8* rhs);

	b8 operator!=(const String& lhs, const String& rhs);
	b8 operator!=(const a8* lhs, const String& rhs);
	b8 operator!=(const String& lhs, const a8* rhs);

	b8 operator<(const String& lhs, const String& rhs);
	b8 operator<(const a8* lhs, const String& rhs);
	b8 operator<(const String& lhs, const a8* rhs);

	b8 operator<=(const String& lhs, const String& rhs);
	b8 operator<=(const a8* lhs, const String& rhs);
	b8 operator<=(const String& lhs, const a8* rhs);

	b8 operator>(const String& lhs, const String& rhs);
	b8 operator>(const a8* lhs, const String& rhs);
	b8 operator>(const String& lhs, const a8* rhs);

	b8 operator>=(const String& lhs, const String& rhs);
	b8 operator>=(const a8* lhs, const String& rhs);
	b8 operator>=(const String& lhs, const a8* rhs);

	std::ostream& operator<<(std::ostream& os, const String& string);
	std::istream& operator>>(std::istream& is, String& string);

	std::istream& getline(std::istream& is, String& string);

}

#endif