#ifndef PROPITIOUS_COMMON_ARCHITECTURES_HPP
#define PROPITIOUS_COMMON_ARCHITECTURES_HPP

namespace Propitious
{

#if defined(_WIN64) || defined (__x86_64__) || defined(__ppc64__) || defined(__WIN64) ||  defined(WIN64)
#define PROPITIOUS_ARCHITECTURE_X64
#define PROPITIOUS_MAXINT_BITS 64
#define PROPITIOUS_MAXINT_BYTES 8
#elif __arm__
#define PROPITIOUS_ARCHITECTURE_ARM
#define PROPITIOUS_MAXINT_BITS 32
#define PROPITIOUS_MAXINT_BYTES 4
	#warning Propitious may not work on this platform, no tests have been performed.
#else
#define PROPITIOUS_ARCHITECTURE_X32
#define PROPITIOUS_MAXINT_BITS 32
#define PROPITIOUS_MAXINT_BYTES 4
#endif

}

#endif