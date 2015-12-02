#include <Propitious/System/SystemInfo.hpp>

namespace Propitious
{
#ifdef PROPITIOUS_SYSTEM_WINDOWS
	namespace Implementation
	{
		static SYSTEM_INFO sysinfo;
		static b8 intialised = false;

		inline void init()
		{
			GetSystemInfo(&sysinfo);
		}

		inline i8 findPhysicalCores()
		{		
			return sysinfo.dwNumberOfProcessors;
		}

		inline i8 findLogicalCores()
		{
			SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* base;
			SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* current;
			DWORD cbRemaining;
			DWORD cb;
			if (GetLogicalProcessorInformationEx(RelationAll, nullptr, &cb))
				return 1;
			if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
				return 1;

			base = reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*>(LocalAlloc(LMEM_FIXED, cb));

			if (!base)
				return 1;

			if (!GetLogicalProcessorInformationEx(RelationAll, base, &cb))
				return 1;

			current = base;
			cbRemaining = cb;

			return 1;
		}
	}

	void make(SystemInfo& info)
	{
		Implementation::init();
		info.physicalCores = Implementation::findPhysicalCores();
		//info.logicalCores = Implementation::findLogicalCores();
	}
#endif
}