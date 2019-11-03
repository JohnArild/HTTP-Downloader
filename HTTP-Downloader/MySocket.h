#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class MySocket
{
	WSADATA winSockData_;
	SOCKET ConnectSocket_;
	WORD wVersionRequested_{ MAKEWORD(2, 2) }; // Winsock DLL version to use
	int errorCode_;
	u_short port_{ htons(27015) }; // host port
	sockaddr_in address_; // host address
	bool isConnected_{ false };
	char recvbuf[512]{ "" };

	int MyConnectIP(PCWSTR IPaddress, int port);
	int MyCreateSocket(int af, int type, int protocol);
	int MyReceive(std::string& result);
	int MyShutdown(std::string& result);
public:
	MySocket(PCWSTR IPaddress, int port);
	~MySocket();
	int GetErrorCode() { return errorCode_; }
	int sendRequest(const std::string &sendString, std::string& result);
	int MyConnect(PCWSTR IPaddress, int port);
	int MyClose(std::string& result);
};

MySocket::MySocket(PCWSTR IPaddress, int port)
{
	errorCode_ = 0;
	// CreateSocket creates a socket that is bound to a specific transport service provider.
	// AF_INET - The Internet Protocol version 4 (IPv4) address family. 
	// SOCK_STREAM - Uses TCP for AF_INET
	// IPPROTO_TCP - The Transmission Control Protocol(TCP)
	errorCode_ = MyCreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	errorCode_ = MyConnectIP(IPaddress, port);
}

MySocket::~MySocket()
{
	WSACleanup();
}

int MySocket::MyCreateSocket(int af, int type, int protocol)
{
	int errorCode{ 0 };
	errorCode = WSAStartup(wVersionRequested_, &winSockData_); //Returns 0 if sucessful
	ConnectSocket_ = socket(af, type, protocol);
	if (errorCode) WSACleanup();
	else if (ConnectSocket_ == INVALID_SOCKET)
	{
		errorCode = WSAGetLastError();
		WSACleanup();
	}
	return errorCode;
}

int MySocket::MyConnectIP(PCWSTR IPaddress, int port)
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
	else isConnected_ = true;
	return errorCode;
}

int MySocket::sendRequest(const std::string &sendString, std::string &result)
{
	int iResult{ 0 };

	if (!isConnected_)
	{
		result = "Not connected, last error message: " + std::to_string(errorCode_) + '\n';
		return 1;
	}
	
	iResult = send(ConnectSocket_, sendString.c_str(), (int)sendString.length(), 0);
	if (iResult == SOCKET_ERROR) {
		errorCode_ = WSAGetLastError();
		closesocket(ConnectSocket_);
		WSACleanup();
		result = "send failed with error: " + std::to_string(errorCode_) + '\n';
		return errorCode_;
	}
	result = "Bytes Sent: " + std::to_string(iResult) + '\n';

	iResult = MyShutdown(result); // Shuts down connection since no more data is being sendt.

	iResult = MyReceive(result); // Receive until the peer closes the connection
	
	return iResult;
}

int MySocket::MyReceive(std::string& result)
{

}

int MySocket::MyShutdown(std::string& result)
{
	int iResult{ 0 };
	iResult = shutdown(ConnectSocket_, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		errorCode_ = WSAGetLastError();
		result += "Shutdown failed with error: "  + std::to_string(errorCode_) + '\n';
		closesocket(ConnectSocket_);
		WSACleanup();
		return 1;
	}
}

int MySocket::MyConnect(PCWSTR IPaddress, int port)
{
	errorCode_ = 0;
	errorCode_ = MyCreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	errorCode_ = MyConnectIP(IPaddress, port);
}

int MySocket::MyClose(std::string& result)
{
	return 0;
}