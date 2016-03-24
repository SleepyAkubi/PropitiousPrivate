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
		DLL(const String& filename)
			: handle()
		{
			const a8* filenameC = cString(filename);
			handle.handle = LoadLibraryExA(filenameC, 0, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
			AssertMsg(GetLastError() == 0, GetLastErrorString())
		}

		void* getFunction(const String& name)
		{
			if (!handle.handle)
				return nullptr;

			const char* functionNameC = cString(name);
			return GetProcAddress(handle.handle, functionNameC);
		}

		static void addDLLDirectory(const String& path)
		{
			const char* cPath = cString(path);
			const size_t cSize = strlen(cPath) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, cPath, cSize);

			AssertMsg(AddDllDirectory(wc) != 0 || GetLastError() == 0, GetLastErrorString());
		}

		~DLL() = default;
	private:
		DLLHandle handle;
	};
}

#endif
