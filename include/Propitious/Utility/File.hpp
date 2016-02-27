#ifndef PROPITIOUS_UTILITY_FILE_HPP
#define PROPITIOUS_UTILITY_FILE_HPP

#include <Propitious/Common.hpp>
#include <Windows.h>
#include <string>

namespace Propitious
{
	namespace
	{
		static std::string exePath;
		static std::string gamePath;
	}

	inline std::string getFileDirectory(const std::string& path)
	{
		usize found = path.find_last_of("/\\");
		return path.substr(0, found);
	}

	inline std::string getPathToExe()
	{
		if (exePath.empty())
		{
			char buffer[2048];
			GetModuleFileName(0, buffer, 2048);
			std::string bufferString = std::string(buffer);
			exePath = getFileDirectory(bufferString);
		}
		return exePath;
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
