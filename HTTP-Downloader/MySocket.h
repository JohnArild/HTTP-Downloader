#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>
#include <list>

#pragma comment(lib, "ws2_32.lib")

class MySocket
{
	WSADATA winSockData_;
	SOCKET ConnectSocket_;
	WORD wVersionRequested_{ MAKEWORD(2, 2) }; // Winsock DLL version to use
	sockaddr_in address_; // host address

	int errorCode_;
	bool isConnected_{ false };
	std::list<char> receiveBuffer_;

	int MyConnectIP(PCWSTR IPaddress, int port);
	int MyCreateSocket(int af, int type, int protocol);
	int MyReceive(std::string& result);
	int MyShutdown(std::string& result);
	int MySend(const std::string& sendString, std::string& result);
public:
	MySocket(PCWSTR IPaddress, int port);
	~MySocket();
	int GetErrorCode() { return errorCode_; }
	int sendRequest(const std::string &sendString, std::string& result);
	int MyConnect(PCWSTR IPaddress, int port);
	int MyClose(std::string& result);
};

