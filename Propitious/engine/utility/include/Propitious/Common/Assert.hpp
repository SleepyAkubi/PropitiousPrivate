#ifndef PROPITIOUS_DEBUG_ASSERT_HPP
#define PROPITIOUS_DEBUG_ASSERT_HPP

#include <Propitious\Common\Architectures.hpp>
#include <Propitious\Common\Types.hpp>
#include <Propitious\Common\Windows.hpp>
#include <iostream>
#include "Windows.h"

namespace Propitious
{
	namespace Internal
	{
		inline void ForceAssert(const char* reason, const char* notes, const char* file, int line)
		{
#ifdef PROPITIOUS_SYSTEM_WINDOWS
#define MAXALEN 2048
			a8 message[MAXALEN] = "";
			sprintf_s(message + strlen(message), MAXALEN, "%s\n\n%s:%d", reason, file, line);
			if (notes != nullptr)
			{
				sprintf_s(message + strlen(message), MAXALEN, "\n\nNotes:\n%s", notes);
			}
			sprintf_s(message + strlen(message), MAXALEN, "\n\nPress TRY AGAIN to break");
			i8 choice = MessageBoxA(0, message, "Assertion Failed!", MB_CANCELTRYCONTINUE | MB_DEFBUTTON2 | MB_ICONWARNING);
			switch (choice)
			{
			case IDCANCEL:
			{
				exit(-1);
				break;
			}
			case IDTRYAGAIN:
			{
				__debugbreak();
				break;
			}
			default:
			{
				break;
			}
			}
#endif
		}
	}

#ifdef _DEBUG
#define AssertMsg(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define FatalError(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define Assert(x) \
	AssertActual(x, nullptr, __FILE__, __LINE__)

#define AssertActual(x, y, file, line) \
	if (!( x ) ) \
		Internal::ForceAssert( #x , y , file, line );
}
#else

#define AssertMsg(x, y)

#define FatalError(x, y)
	// error handling

#define Assert(x)
}
#endif
#endif