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
			const wchar* filenameC = cString(filename);
			handle.handle = LoadLibrary(filenameC);
		}

		~DLL() = default;

		void* getFunction(const String& name)
		{
			if (!handle.handle)
				return nullptr;

			const char* functionNameC = unwiden(cString(name));
			return GetProcAddress(handle.handle, functionNameC);
		}

		static void addDLLDirectory(const String& path)
		{
			SetDllDirectory(cString(path));
		}
	private:
		DLLHandle handle;
	};
}

#endif
