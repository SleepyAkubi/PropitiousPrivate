#include <Propitious/Containers/String.hpp>

namespace Propitious
{
	namespace
	{
		inline i32 compare(const String& lhs, const String& rhs)
		{
			const wchar* string1 = cString(lhs);
			const wchar* string2 = cString(rhs);

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
	inline String::String(wchar character, Allocator& allocator)
		: data(allocator)
	{
		append(data, character);
	}
	inline String::String(const wchar* characterArray, Allocator& allocator)
		: data(allocator)
	{
		append(data, characterArray, wcslen(characterArray));
	}
	inline String::String(const a8* characterArray, Allocator& allocator)
	{
		const wchar* widened = widen(characterArray);
		append(data, widened, wcslen(widened));
	}

	inline const wchar* widenString(const a8* string)
	{
		const usize size = strlen(string) + 1;
		wchar* widenedChars = new wchar[size];
		mbstowcs(widenedChars, string, size);

		return widenedChars;
	}
	inline const a8* unwiden(const wchar* string)
	{
		const usize size = wcslen(string) + 1;
		char* unwidenedChars = new char[size];
		wcstombs(unwidenedChars, string, size);

		return unwidenedChars;
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
	inline String& String::operator=(const wchar* characterArray)
	{
		clear(data);
		append(data, characterArray, wcslen(characterArray));
		return *this;
	}
	inline String& String::operator=(const wchar character)
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

	inline usize append(String& string, wchar character)
	{
		return append(string.data, character);
	}
	inline usize append(String& string, const wchar* characterArray)
	{
		return append(string.data, characterArray, wcslen(characterArray));
	}
	inline usize append(String& string, const String& string2)
	{
		return append(string.data, &front(string2), length(string2));
	}

	inline wchar* begin(String& string)
	{
		return begin(string.data);
	}
	inline const wchar* begin(const String& string)
	{
		return begin(string.data);
	}
	inline wchar* end(String& string)
	{
		return end(string.data);
	}
	inline const wchar* end(const String& string)
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
		return (usize)-1;
	}

	inline Array<const wchar*> split(const String& string, wchar delim)
	{
		Array<const wchar*> elems;

		const wchar* cstr = cString(string);
		usize strLength = length(string);
		usize start = 0;
		usize end = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == delim)
					break;
				end++;
			}

			append(elems, cString(substring(string, start, end)));
			start = end + 1;
			end = start;
		}

		return elems;
	}

	inline usize findLast(const String& string, const String& sub)
	{
		usize subLength = length(sub);
		for (usize i = length(string) - subLength; i >= 0; i--)
		{
			String portion = substring(string, i, i + subLength);
			if (portion == sub)
				return i;
		}
		return -1;
	}

	inline wchar& front(String& string)
	{
		return string.data[0];
	}
	inline const wchar& front(const String& string)
	{
		return string.data[0];
	}
	inline wchar& back(String& string)
	{
		return string.data[string.data.length - 1];
	}
	inline const wchar& back(const String& string)
	{
		return string.data[string.data.length - 1];
	}

	inline const wchar* cString(const String& string)
	{
		append(const_cast<Array<wchar>&>(string.data), L'\0');
		dele(const_cast<Array<wchar>&>(string.data));
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

	inline String operator+(const String& lhs, const wchar* rhs)
	{
		String output = lhs;
		append(output, rhs);
		return output;
	}
	inline String operator+(const wchar* lhs, const String& rhs)
	{
		String output = (const wchar*)lhs;
		append(output, rhs);
		return output;
	}

	inline String operator+(const String& lhs, wchar rhs)
	{
		String output = lhs;
		append(output, rhs);
		return output;
	}
	inline String operator+(wchar lhs, const String& rhs)
	{
		String output = (wchar)lhs;
		append(output, rhs);
		return output;
	}

	inline b8 operator==(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) == 0;
	}
	inline b8 operator==(const wchar* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) == 0;
	}
	inline b8 operator==(const String& lhs, const wchar* rhs)
	{
		return compare(cString(lhs), rhs) == 0;
	}

	inline b8 operator!=(const String& lhs, const String& rhs)
	{
		return !operator==(lhs, rhs);
	}
	inline b8 operator!=(const wchar* lhs, const String& rhs)
	{
		return !operator==(lhs, rhs);
	}
	inline b8 operator!=(const String& lhs, const wchar* rhs)
	{
		return !operator==(lhs, rhs);
	}

	inline b8 operator<(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) < 0;
	}
	inline b8 operator<(const wchar* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) < 0;
	}
	inline b8 operator<(const String& lhs, const wchar* rhs)
	{
		return compare(cString(lhs), rhs) < 0;
	}

	inline b8 operator<=(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) <= 0;
	}
	inline b8 operator<=(const wchar* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) <= 0;
	}
	inline b8 operator<=(const String& lhs, const wchar* rhs)
	{
		return compare(cString(lhs), rhs) <= 0;
	}

	inline b8 operator>(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) > 0;
	}
	inline b8 operator>(const wchar* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) > 0;
	}
	inline b8 operator>(const String& lhs, const wchar* rhs)
	{
		return compare(cString(lhs), rhs) > 0;
	}

	inline b8 operator>=(const String& lhs, const String& rhs)
	{
		return compare(lhs, rhs) >= 0;
	}
	inline b8 operator>=(const wchar* lhs, const String& rhs)
	{
		return compare(lhs, cString(rhs)) >= 0;
	}
	inline b8 operator>=(const String& lhs, const wchar* rhs)
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
		char character = '\0';
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
		char character;
		clear(string);
		while (inputStream.get(character) && character != '\n')
			append(string, character);
		return inputStream;
	}
}