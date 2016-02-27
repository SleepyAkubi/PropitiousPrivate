#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	namespace
	{
		inline i32 compare(const String& lhs, const String& rhs)
		{
			const a8* string1 = cString(lhs);
			const a8* string2 = cString(rhs);

			while (*string1 && (*string1 == *string2))
			{
				string1++;
				string2++;
			}

			return *(const u8*)(string1)-*(const u8*)(string2);
		}
	}

	inline String::String(Allocator& allocator)
		: data(allocator)
	{

	}
	inline String::String(a8 character, Allocator& allocator)
		: data(allocator)
	{
		append(data, character);
	}
	inline String::String(const a8* characterArray, Allocator& allocator)
		: data(allocator)
	{
		append(data, characterArray, strlen(characterArray));
	}
	inline String::String(const String& string)
		: data(string.data)
	{

	}

	inline String& String::operator=(const String& string)
	{
		data = string.data;
		return *this;
	}
	inline String& String::operator=(const a8* characterArray)
	{
		clear(data);
		append(data, characterArray, strlen(characterArray));
		return *this;
	}
	inline String& String::operator=(const a8 character)
	{
		clear(data);
		append(data, character);
		return *this;
	}

	inline usize length(const String& string)
	{
		return length(string.data);
	}
	inline usize capacity(const String& string)
	{
		return capacity(string.data);
	}

	inline usize append(String& string, a8 character)
	{
		return append(string.data, character);
	}
	inline usize append(String& string, const a8* characterArray)
	{
		return append(string.data, characterArray, strlen(characterArray));
	}
	inline usize append(String& string1, const String& string2)
	{
		return append(string1.data, front(string2));
	}

	inline a8* begin(String& string)
	{
		return begin(string.data);
	}
	inline const a8* begin(const String& string)
	{
		return begin(string.data);
	}
	inline a8* end(String& string)
	{
		return end(string.data);
	}
	inline const a8* end(const String& string)
	{
		return end(string.data);
	}

	inline usize find(const String& string, const String& sub)
	{
		usize subLength = length(sub);
		for (usize i = 0; i < length(string); i++)
		{
			String portion = substring(string, i, i + length(sub));
			if (portion == sub)
				return i;
		}
		return -1;
	}

	inline a8& front(String& string)
	{
		return string.data[0];
	}
	inline const a8& front(const String& string)
	{
		return string.data[0];
	}
	inline a8& back(String& string)
	{
		return string.data[string.data.length - 1];
	}
	inline const a8& back(const String& string)
	{
		return string.data[string.data.length - 1];
	}

	inline const a8* cString(const String& string)
	{
		append(const_cast<Array<a8>&>(string.data), '\0');
		dele(const_cast<Array<a8>&>(string.data));
		return begin(string.data);
	}

	inline void clear(String& string)
	{
		clear(string.data);
	}

	inline void trim(String& string)
	{
		trim(string.data);
	}

	inline void resize(String& string, usize length)
	{
		resize(string.data, length);
	}

	inline void reserve(String& string, usize capacity)
	{
		reserve(string.data, capacity);
	}

	String substring(const String& s, usize begin, usize end)
	{
		if (end >= length(s))
			end = length(s);

		String output(*s.data.allocator);
		vol length = end - begin;

		reserve(output, length);
		
		for (vol i = begin; i < end; i++)
			append(output, s[i]);

		return output;
	}

	inline String operator+(const String& lhs, const String& rhs)
	{
		String output = lhs;
		append(output, rhs);
		return output;
	}

	inline String operator+(const String& lhs, const a8* rhs)
	{
		String output = lhs;
		append(output, rhs);
		return output;
	}
	inline String operator+(const a8* lhs, const String& rhs)
	{
		String output = (const a8*)lhs;
		append(output, rhs);
		return output;
	}

	inline String operator+(const String& lhs, a8 rhs)
	{
		String output = lhs;
		append(output, rhs);
		return output;
	}
	inline String operator+(a8 lhs, const String& rhs)
	{
		String output = (a8)lhs;
		append(output, rhs);
		return output;
	}

	inline b8 operator==(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) == 0;
	}
	inline b8 operator==(const a8* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) == 0;
	}
	inline b8 operator==(const String& lhs, const a8* rhs)
	{
		return compare(cString(lhs), rhs) == 0;
	}

	inline b8 operator!=(const String& lhs, const String& rhs)
	{
		return !operator==(lhs, rhs);
	}
	inline b8 operator!=(const a8* lhs, const String& rhs)
	{
		return !operator==(lhs, rhs);
	}
	inline b8 operator!=(const String& lhs, const a8* rhs)
	{
		return !operator==(lhs, rhs);
	}

	inline b8 operator<(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) < 0;
	}
	inline b8 operator<(const a8* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) < 0;
	}
	inline b8 operator<(const String& lhs, const a8* rhs)
	{
		return compare(cString(lhs), rhs) < 0;
	}

	inline b8 operator<=(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) <= 0;
	}
	inline b8 operator<=(const a8* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) <= 0;
	}
	inline b8 operator<=(const String& lhs, const a8* rhs)
	{
		return compare(cString(lhs), rhs) <= 0;
	}

	inline b8 operator>(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) > 0;
	}
	inline b8 operator>(const a8* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) > 0;
	}
	inline b8 operator>(const String& lhs, const a8* rhs)
	{
		return compare(cString(lhs), rhs) > 0;
	}

	inline b8 operator>=(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) >= 0;
	}
	inline b8 operator>=(const a8* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) >= 0;
	}
	inline b8 operator>=(const String& lhs, const a8* rhs)
	{
		return compare(cString(lhs), rhs) >= 0;
	}

	std::ostream& operator<<(std::ostream& outputStream, const String& string)
	{
		outputStream << cString(string);
		return outputStream;
	}
	std::istream& operator>>(std::istream& inputStream, String& string)
	{
		a8 character = '\0';
		for (;;)
		{
			if (inputStream.eof())
				break;
			inputStream >> character;
			if (character != '\0')
				break;

			append(string, character);
		}
		return inputStream;
	}

	std::istream& getline(std::istream& inputStream, String& string)
	{
		a8 character;
		clear(string);
		while (inputStream.get(character) && character != '\n')
			append(string, character);
		return inputStream;
	}
}