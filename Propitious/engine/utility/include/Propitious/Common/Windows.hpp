#ifndef PROPITIOUS_COMMON_WINDOWS_HPP
#define PROPITIOUS_COMMON_WINDOWS_HPP

#include <Propitious/Common/BasicDefinitions.hpp>
#include <Propitious/Common/OperatingSystems.hpp>
#include <Propitious/Common/Types.hpp>

#ifdef PROPITIOUS_SYSTEM_WINDOWS

namespace Propitious
{
	PROPITIOUS_UTILITY_EXPORT const char* GetLastErrorString();
}

#endif

#endif