#ifndef PROPITIOUS_COMMON_DEBUGONLY
#define PROPITIOUS_COMMON_DEBUGONLY

namespace Propitious
{
#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG) || defined(_DEBUG_) || defined(__DEBUG__) || defined(PROPITIOUS_DEBUG)
#define debug(x) x
#else
#define debug(x)
#endif
}

#endif