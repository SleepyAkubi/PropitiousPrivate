#include <Propitious/Networking/Server.hpp>

#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>


namespace Propitious
{
	Server::Server(b8 udp, i16 port)
	{
		i8 currentResult;
		currentResult = (i8)WSAStartup(MAKEWORD(2, 2), &data.wsaData);
		if (currentResult != 0)
		{
			// Error Handling
		}
		addrinfo* result = nullptr;
		addrinfo* ptr = nullptr;
		addrinfo hints = { 0 };

		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		if (udp)
			hints.ai_protocol = IPPROTO_UDP;
		else
			hints.ai_protocol = IPPROTO_TCP;

		hints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &result) != 0)
		{
			// Error Handling
			WSACleanup();
			return;
		}

		SOCKET listenSocket = INVALID_SOCKET;
		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET)
		{
			// Error Handling
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		if (bind(listenSocket, result->ai_addr, (i32)result->ai_addrlen) == SOCKET_ERROR)
		{
			// Error Handling
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);

		if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			// Error Handling
			closesocket(listenSocket);
			WSACleanup();
		}

		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			// Error Handling
			closesocket(listenSocket);
			WSACleanup();
		}

		closesocket(listenSocket);
	}
}
