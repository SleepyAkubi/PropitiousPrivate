#ifndef PROPITIOUS_COMMON_BASICSTRINGFUNCTIONS_HPP
#define PROPITIOUS_COMMON_BASICSTRINGFUNCTIONS_HPP

#include <Windows.h>

namespace Propitious
{

	wchar_t* widen(const char* charArray)
	{
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

}

#endif