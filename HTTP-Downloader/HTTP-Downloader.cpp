/* HTTP-Downloader.cpp : This file contains the 'main' function. Program execution begins and ends there.
* Note that the code is Windows spesific (uses Ws2_32.dll and WinSock2.h).
*/

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA winSockData;
	WORD wVersionRequested = MAKEWORD(1, 0); // Winsock DLL version to use
	if (WSAStartup(wVersionRequested, &winSockData)) //Returns 0 if sucessful
	{
		std::cout << "Winsocket did not start" << std::endl;
	}
	else 
		std::cout << "Winsocket started" << std::endl;
	WSACleanup(); //terminates use of the Winsock 2 DLL
    std::cout << "Hello World!\n";
}

