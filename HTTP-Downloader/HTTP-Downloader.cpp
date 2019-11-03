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
	//Downloads http://www.columbia.edu/~fdc/sample.html 
	//I chose that site since it does not use https and is plain html
	//It was also the first result when I searched "plain html site"
	std::string requestString = ""; // Holds the HTTP request string
	requestString += "GET /~fdc/sample.html HTTP/1.1\r\n";
	requestString += "Host: www.columbia.edu\r\n";
	requestString += "Connection: close\r\n\r\n";
	MySocket wsaSocket(__TEXT("128.59.105.24"), 80); //IP address of  www.columbia.edu

	int errorcode{ 0 };
	std::string resultString;

	if (wsaSocket.GetErrorCode())
		std::cout << "Winsocket did not start" << std::endl;
	else 
	{
		std::cout << "Winsocket started" << std::endl;
		std::cout << "Sending string to server" << std::endl;
		wsaSocket.sendRequest(requestString, resultString);
		std::cout << resultString;
	}
	std::cout << "Error code: " << wsaSocket.GetErrorCode() << std::endl;

	std::cout << "Do you want to see the output? ";
	std::string answer{ "" };
	std::cin >> answer;
	if(answer == "yes" || answer == "y") wsaSocket.printBuffer();
}

