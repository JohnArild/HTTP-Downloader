#pragma once

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class MySocket
{
	WSADATA winSockData_;
	WORD wVersionRequested_;
	int errorCode_;
public:
	MySocket();
	~MySocket();
	int GetErrorCode() { return errorCode_; }
};

MySocket::MySocket()
{
	wVersionRequested_ = MAKEWORD(2, 2); // Winsock DLL version to use
	errorCode_ = WSAStartup(wVersionRequested_, &winSockData_); //Returns 0 if sucessful
}

MySocket::~MySocket()
{
	WSACleanup();
}