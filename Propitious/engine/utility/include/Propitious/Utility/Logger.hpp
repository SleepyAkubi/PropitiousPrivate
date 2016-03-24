#ifndef PROPITIOUS_EXTRAS_LOGGER_HPP
#define PROPITIOUS_EXTRAS_LOGGER_HPP

#include <Propitious/Common.hpp>
#include <stdio.h>

namespace Propitious
{
	enum class LogFlags : u32
	{
		Date = 1,
		Time = 2,
		Default = Date | Time
	};

	struct Logger
	{
		FILE* file;
		LogFlags flags;
		const a8* prefix;
	};

	namespace Log
	{
		PROPITIOUS_EXPORT void Print(const Logger& logger, const a8* format, ...);
	}
}

#endif
