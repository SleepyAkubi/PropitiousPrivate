#ifndef PROPITIOUS_COMMON_MODIFIERS
#define PROPITIOUS_COMMON_MODIFIERS

namespace Propitious
{
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
}
#endif