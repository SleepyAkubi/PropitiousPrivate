#ifndef PROPITIOUS_SYSTEM_SYSTEM_HPP
#define PROPITIOUS_SYSTEM_SYSTEM_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{

	namespace Implementation
	{
		void init();
		i8 findProcessors();
	}

	struct PROPITIOUS_EXPORT SystemInfo
	{
		i8 logicalCores;
		i8 physicalCores;

		i64 ramInBytes;
	};

	void PROPITIOUS_EXPORT make(SystemInfo& info);
}

#endif