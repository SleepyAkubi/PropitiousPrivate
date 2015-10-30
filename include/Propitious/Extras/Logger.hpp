#ifndef PROPITIOUS_EXTRAS_LOGGER_HPP
#define PROPITIOUS_EXTRAS_LOGGER_HPP

#include <Propitious/Common.hpp>
#include <stdio.h>

namespace Propitious
{
	struct Logger
	{
		FILE* file;
		u32 flags;
		const char* prefix;
	};

	namespace Log
	{
		PROPITIOUS_EXPORT void Print(const Logger& logger, const char* format, ...);
	}
}

#endif
