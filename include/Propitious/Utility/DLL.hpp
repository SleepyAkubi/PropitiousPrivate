#ifndef PROPITIOUS_UTILITY_DLL_HPP
#define PROPITIOUS_UTILITY_DLL_HPP

#include "Propitious\Common.hpp"
#include "Propitious\Utility\File.hpp"
#include <Windows.h>
#include <string>

namespace Propitious
{
#ifdef PROPITIOUS_SYSTEM_WINDOWS
	struct DLLHandle
	{
		HMODULE handle;
	};
#endif

	class DLL
	{
	public:
		DLL(const std::string& filename)
			: handle()
		{
			const char* filenameC = filename.c_str();
			handle.handle = LoadLibrary(filenameC);
		}

		~DLL() = default;

		void* getFunction(std::string name)
		{
			if (!handle.handle)
				return nullptr;

			const char* functionNameC = name.c_str();
			return GetProcAddress(handle.handle, functionNameC);
		}

		static void addDLLDirectory(const std::string& path)
		{
			SetDllDirectory(path.c_str());
		}
	private:
		DLLHandle handle;
	};
}

#endif
