#include <Propitious/Common/Windows.hpp>

#include <Windows.h>

namespace Propitious
{
	const char* GetLastErrorString()
	{
		u32 errorMessageID = GetLastError();
		if (errorMessageID == 0)
			return nullptr;

		LPSTR messageBuffer = nullptr;
		usize size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		return messageBuffer;
	}
}