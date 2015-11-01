#ifndef PROPITIOUS_COMMON_MESSAGES_HPP
#define PROPITIOUS_COMMON_MESSAGES_HPP

#include <Propitious/Common/Compilers.hpp>

namespace Propitious
{
	// stringised version of line number (must be done in two steps)
#define STRINGISE(N) #N
#define EXPAND_THEN_STRINGISE(N) STRINGISE(N)
#define __LINE_STR__ EXPAND_THEN_STRINGISE(__LINE__)

	// MSVC-suitable routines for formatting <#pragma message>
#define __LOC__ __FILE__ "(" __LINE_STR__ ")"
#define __OUTPUT_FORMAT__(type) __LOC__ " : " type " : "

	// specific message types for <#pragma message>
#define PROPITIOUS_WARNING(x) __OUTPUT_FORMAT__("warning" x)
#define PROPITIOUS_ERROR(x) __OUTPUT_FORMAT__("error" x)
}
#endif