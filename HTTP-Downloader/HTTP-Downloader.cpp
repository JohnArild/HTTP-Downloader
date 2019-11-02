/* HTTP-Downloader.cpp : This file contains the 'main' function. Program execution begins and ends there.
* Note that the code is Windows spesific (uses Ws2_32.dll and WinSock2.h).
*/

#include <iostream>
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

int main()
{
	MySocket wsaSocket;
	if (wsaSocket.GetErrorCode())
	{
		std::cout << "Winsocket did not start" << std::endl;
	}
	else 
		std::cout << "Winsocket started" << std::endl;
    std::cout << "Hello World!\n";
}

