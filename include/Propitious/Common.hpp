#ifndef PROPITIOUS_COMMON_HPP
#define PROPITIOUS_COMMON_HPP

#include <cstdint>
#include <cstddef>

#include <cassert>
#include <functional>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

#include <tchar.h>

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
	#define propexp __declspec(dllexport)
	#else
	#define propexp __declspec(dllimport)
	#endif

	#define old				__declspec(deprecated)
		//#define appdomain		__declspec(appdomain)
		//#define jitintrinsic	__declspec(jitintrinsic)
		//#define exposed			__declspec(naked)
		//#define noalias		__declspec(noalias)
	#define dontinline		__declspec(noinline)
	#define makeinline		__forceinline
	#define dontreturn		__declspec(noreturn)
	#define noexception		__declspec(nothrow)
	#ifndef _MSC_VER
	#define pure	__declspec(novtable) class
	#else
	#define pure	__interface
	#endif
	//#define process			__declspec(process)
	#define nopointeralias	__declspec(restrict)
	#define pickanyCOMDAT	__declspec(selectany)
	#define threadlocal		__declspec(thread)

	#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG)
	#define debug(x) x
	#else
	#define debug(x)
	#endif

	template <class T, class... Args>
	std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template <class T, class... Args>
	std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args)
	{
		static_assert(
			std::extent<T>::value == 0,
			"make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

		typedef typename std::remove_extent<T>::type U;
		return std::unique_ptr<T>(
			new U[sizeof...(Args)]{ std::forward<Args>(args)... });
	}

	template <class T, class... Args>
	std::unique_ptr<T> make_unique(Args&&... args)
	{
		return make_unique_helper<T>(std::is_array<T>(),
			std::forward<Args>(args)...);
	}

	template <typename T, typename U>
	inline T pseudo_cast(const U& x)
	{
		T to = T(0);
		memcpy(&to, &x, (sizeof(T) < sizeof(U)) ? sizeof(T) : sizeof(U));
		return to;
	}

	#if defined(_WIN32) || defined (_WIN64) || defined (__WIN32) || defined (__WIN64) || defined (WIN32) || defined (WIN64)
	#define PROPITIOUS_SYSTEM_WINDOWS

	#ifndef NOMINMAX
	#define NOMINMAX
	#endif
	#elif defined (__APPLE__) && defined(__MACH__)
	#define PROPITIOUS_SYSTEM_OSX
	#define PROPITIOUS_SYSTEM_UNIX
	#elif defined (__unix__)
	#define PROPITIOUS_SYSTEM_UNIX
	#if defined (__linux__)
	#define PROPITIOUS_SYSTEM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	#define PROPITIOUS_SYSTEM_FREEBSD
		//#error FreeBSD is not supported by bGame4
	#else
	#define PROPITIOUS_SYSTEM_OTHER_UNIX
		//#error This UNIX-based system is not supported by Propitious
	#endif
	#else
		//#error This operating system is not supported by Propitious
	#endif

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

	#if   defined(_MSC_VER)
	#define PROPITIOUS_COMPILER_MSVC
	#elif defined(__clang__)
	#define PROPITIOUS_COMPILER_CLANG
	#elif defined(__GNUC__) || defined(__GNUG__) && !(defined(__clang__))
	#define PROPITIOUS_COMPILER_GNU_GCC
	#elif defined(__INTEL_COMPILER)
	#define PROPITIOUS_COMPILER_INTEL
	#endif

	#if defined(UNICODE)
	#define PROPITIOUS_CHARSET_UNICODE
	#else
	#define PROPITIOUS_CHARSET_ANSI
	#endif

	#ifndef _MSC_VER
	#define NOEXCEPT noexcept
	#else
	#define NOEXCEPT
	#endif

	class propexp NonCopyable
	{
	protected:
		NonCopyable() {}
	private:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	};

	/* Do Not Use */
	template <typename T>
	class Hooked : private NonCopyable
	{
	public:
		using Function = std::function<void(const T&, const T&)>;
		Hooked(T& value, Function hook) : reference(value), hook(hook) {}

		T& operator=(const T& value)
		{
			hook(reference, value);
			reference = value;
		}

		T& reference;
		Function hook;
	};

}

#define PROPITIOUS_HASH_MURMUR

#include <Propitious/Types.hpp>
#include <Propitious/Memory/Allocator.hpp>

#endif