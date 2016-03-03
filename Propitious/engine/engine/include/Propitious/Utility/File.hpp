#ifndef PROPITIOUS_UTILITY_FILE_HPP
#define PROPITIOUS_UTILITY_FILE_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Containers/String.hpp>
#include <Windows.h>
#include <string>

namespace Propitious
{
	inline String getFileDirectory(const String& path)
	{
		usize found = findLast(path, "\\");
		return substring(path, 0, found);
	}

	inline String getPathToExe()
	{
		wchar buffer[2048];
		GetModuleFileName(0, buffer, 2048);
		String bufferString = String(buffer);
		return getFileDirectory(bufferString);
	}

	/*inline std::string getPathToGame()
	{
		if (gamePath.empty())
		{
			char buffer[2048];
			GetModuleFileName(0, buffer, 2048);
			std::string bufferString = std::string(buffer);
			gamePath = getFileDirectory(bufferString);
			gamePath += 
		}
		return gamePath;
	}*/
}

#endif
