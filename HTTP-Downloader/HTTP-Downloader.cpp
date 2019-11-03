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
	MySocket wsaSocket(__TEXT("216.58.207.227"), 80);
	int errorcode{ 0 };
	std::string resultString;

	if (wsaSocket.GetErrorCode())
		std::cout << "Winsocket did not start" << std::endl;
	else 
	{
		std::cout << "Winsocket started" << std::endl;
		std::cout << "Sending string to server" << std::endl;
		wsaSocket.sendRequest("GET / HTTP/1.1\r\n\r\n", resultString);
		std::cout << resultString;
	}
	std::cout << "Error code: " << wsaSocket.GetErrorCode() << std::endl;
	std::cout << "Do you want to see the output? ";

	std::string answer{ "" };
	std::cin >> answer;
	if(answer == "yes" || answer == "y") wsaSocket.printBuffer();
}

