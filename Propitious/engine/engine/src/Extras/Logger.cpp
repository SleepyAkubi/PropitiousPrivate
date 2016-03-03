#include <Propitious/Utility/Logger.hpp>
#include <Propitious/Math/Time.hpp>

#include <cstdarg>
#include <cstring>

namespace Propitious
{
	namespace Log
	{
		void Print(const Logger& logger, const a8* format, ...)
		{
			static a8 buffer[1024];
			strncpy(buffer, logger.prefix, 1024);
			strncat(buffer, " ", 1);

			if ((u32)logger.flags & (u32)LogFlags::Date)
			{
				const a8* dateString = Time::now().format("%d/%m/%Y");
				strncat(buffer, dateString, strlen(dateString));
				strncat(buffer, " ", 1);
			}

			if ((u32)logger.flags & (u32)LogFlags::Time)
			{
				const a8* dateString = Time::now().format("%H:%M:%S");
				strncat(buffer, dateString, strlen(dateString));
				strncat(buffer, " ", 1);
			}

			strncat(buffer, format, strlen(format));

			va_list variadicArgumentsList;
			va_start(variadicArgumentsList, format);
			{
				vfprintf(logger.file, buffer, variadicArgumentsList);
			}
			va_end(variadicArgumentsList);
		}
	}
}