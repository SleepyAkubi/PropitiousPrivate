#ifndef PROPITIOUS_UTILITY_FILE_HPP
#define PROPITIOUS_UTILITY_FILE_HPP

#include <Windows.h>
#include <string>

namespace Propitious
{
	namespace
	{
		static std::string path;
	}

	inline std::string getFileDirectory(const std::string& path)
	{
		usize found = path.find_last_of("/\\");
		return path.substr(0, found);
	}

	inline std::string getPathToExe()
	{
		if (path.empty())
		{
			char buffer[2048];
			GetModuleFileName(0, buffer, 2048);
			std::string bufferString = std::string(buffer);
			path = getFileDirectory(bufferString);
		}
		return path;
	}

}

#endif
