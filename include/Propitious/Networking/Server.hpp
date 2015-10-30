#ifndef PROPITIOUS_NETWORKING_SERVER_HPP
#define PROPITIOUS_NETWORKING_SERVER_HPP

#include <Propitious/Common.hpp>

#ifdef PROPITIOUS_SYSTEM_WINDOWS
	#include <winsock2.h>
#endif

namespace Propitious
{

	class Server : private NonCopyable
	{
	public:
#ifdef PROPITIOUS_SYSTEM_WINDOWS
		struct Data
		{
			WSADATA wsaData;
		};
#endif
		Server(b8 udp = false, i16 port = 27015);
		Data data;
	};
}

#endif