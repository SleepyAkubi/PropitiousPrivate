#ifndef PROPITIOUS_COMMON_OPERATINGSYSTEMS
#define PROPITIOUS_COMMON_OPERATINGSYSTEMS

#include <Propitious/Common/Messages.hpp>

namespace Propitious
{
#if defined(_WIN32) || defined (_WIN64) || defined (__WIN32) || defined (__WIN64) || defined (WIN32) || defined (WIN64)
#define PROPITIOUS_SYSTEM_WINDOWS

#elif defined (__APPLE__) && defined(__MACH__)
#define PROPITIOUS_SYSTEM_OSX
#define PROPITIOUS_SYSTEM_UNIX
#elif defined (__unix__)
#define PROPITIOUS_SYSTEM_UNIX
#if defined (__linux__)
#define PROPITIOUS_SYSTEM_LINUX
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define PROPITIOUS_SYSTEM_FREEBSD
	#pragma message( PROPITIOUS_ERROR("P-001") "FreeBSD is not supported by Propitious" )
#else
#define PROPITIOUS_SYSTEM_OTHER_UNIX
	#pragma message( PROPITIOUS_ERROR("P-001") "This UNIX-based system is not supported by Propitious" )
#endif
#else
	#pragma message( PROPITIOUS_ERROR("P-001") "This operating system is not supported by Propitious" )
#endif
}
#endif