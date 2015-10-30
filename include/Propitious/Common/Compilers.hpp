#ifndef PROPITIOUS_COMMON_COMPILERS
#define PROPITIOUS_COMMON_COMPILERS

namespace Propitious
{
#if   defined(_MSC_VER)
#define PROPITIOUS_COMPILER_MSVC
#elif defined(__clang__)
#define PROPITIOUS_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__) && !(defined(__clang__))
#define PROPITIOUS_COMPILER_GNU_GCC
#elif defined(__INTEL_COMPILER)
#define PROPITIOUS_COMPILER_INTEL
#endif
}

#endif