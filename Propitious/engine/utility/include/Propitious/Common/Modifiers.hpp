#ifndef PROPITIOUS_COMMON_MODIFIERS_HPP
#define PROPITIOUS_COMMON_MODIFIERS_HPP

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
#define abstract		__declspec(novtable)
#ifdef _MSC_VER
#define interface		__interface
#else
#define	interface		abstract class
#endif
//#define process			__declspec(process)
#define nopointeralias	__declspec(restrict)
#define pickanyCOMDAT	__declspec(selectany)
#define threadlocal		__declspec(thread)
}
#endif