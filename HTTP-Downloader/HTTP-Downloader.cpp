/* HTTP-Downloader.cpp
* by John Arild Lolland (usn id 060419)
* 
* USN fag: DFON2110-1 19H, Oppgave: Nettverk - Nettleser
*
* Note that the code is Windows spesific (uses Ws2_32.dll and WinSock2.h).
* Main source for info was https://docs.microsoft.com/en-us/windows/win32/api/winsock2/
*/

#include <iostream>
#include "MySocket.h"

int main()
{
	MySocket wsaSocket(__TEXT("192.168.8.1"), 80);
	int errorcode{ 0 };

	if (wsaSocket.GetErrorCode())
		std::cout << "Winsocket did not start" << std::endl;
	else 
		std::cout << "Winsocket started" << std::endl;
	std::cout << "Error code: " << wsaSocket.GetErrorCode() << std::endl;
}

