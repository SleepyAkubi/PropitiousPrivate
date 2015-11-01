#ifndef PROPITIOUS_COMMON_BASICDEFINITIONS_HPP
#define PROPITIOUS_COMMON_BASICDEFINITIONS_HPP

namespace Propitious
{
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if _MSC_VER < 1900
#define alignof(x) __alignof(x)
#endif

#if defined( PROPITIOUS_EXPORTS )
	//#define useful
#define PROPITIOUS_EXPORT __declspec(dllexport)
#else
#define PROPITIOUS_EXPORT __declspec(dllimport)
#endif

#define PROPITIOUS_HASH_MURMUR

#pragma warning(disable: 4067)

#if defined(__clang__) && __has_feature(cxx_noexcept) || \
	defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46 || \
	defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180021114
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#pragma warning(default: 4067)
}

#endif