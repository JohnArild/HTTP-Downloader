#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class MySocket
{
	WSADATA winSockData_;
	SOCKET ConnectSocket_;
	WORD wVersionRequested_{ MAKEWORD(2, 2) }; // Winsock DLL version to use
	int errorCode_;
	u_short port_{ htons(27015) }; // host port
	sockaddr_in address_; // host address
	int ConnectIP(PCWSTR IPaddress, int port);
	int ConnectSocket();
public:
	MySocket(PCWSTR IPaddress, int port);
	~MySocket();
	int GetErrorCode() { return errorCode_; }
};

MySocket::MySocket(PCWSTR IPaddress, int port)
{
	errorCode_ = WSAStartup(wVersionRequested_, &winSockData_); //Returns 0 if sucessful
	// socket() creates a socket that is bound to a specific transport service provider.
	// AF_INET - The Internet Protocol version 4 (IPv4) address family. 
	// SOCK_STREAM - Uses TCP for AF_INET
	// IPPROTO_TCP - The Transmission Control Protocol(TCP)
	ConnectSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (errorCode_) WSACleanup();
	else if (ConnectSocket_ == INVALID_SOCKET)
	{
		errorCode_ = WSAGetLastError();
		WSACleanup();
	}
	errorCode_ = ConnectIP(IPaddress, port);
}

MySocket::~MySocket()
{
	WSACleanup();
}

int MySocket::ConnectSocket()
{
	return 0;
}

int MySocket::ConnectIP(PCWSTR IPaddress, int port)
{
	int errorCode{ 0 };
	address_.sin_family = AF_INET;
	InetPton(AF_INET, IPaddress, &address_.sin_addr.s_addr);
	address_.sin_port = htons(port);
	if (connect(ConnectSocket_, (SOCKADDR*)&address_, sizeof(address_)))
	{
		errorCode = WSAGetLastError();
		closesocket(ConnectSocket_);
		WSACleanup();
	}
	return errorCode;
}