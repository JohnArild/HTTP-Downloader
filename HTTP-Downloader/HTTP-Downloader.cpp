/* HTTP-Downloader.cpp : This file contains the 'main' function. Program execution begins and ends there.
* Note that the code is Windows spesific (uses Ws2_32.dll and WinSock2.h).
*/

#include <iostream>
#include "MySocket.h"

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

