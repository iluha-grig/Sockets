#define _WINSOCK_DEPRECATED_NO_WARNINGS
//This is to turn off warnings applied
//to inet_addr function

#pragma comment (lib, "Ws2_32.lib")
//Add static libraries and "import libraries"
//to dependences of project
//Also it can be done through setting of linker

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

int main()
{
	char buf[1000];
	int socklen_client1;
	WSADATA w_data;
	// WSA - Windows Socket API

	SOCKET soc, soc_client1;
	if (WSAStartup(MAKEWORD(2, 2), &w_data) == 0)
	{
		cerr << "WSA startup succes" << endl;
	}
	//WSAStartup function initiates use of the
	//Winsock 2 DLL by a process

	soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soc == SOCKET_ERROR)
	{
		perror("socket not created");
		exit(1);
	}
	sockaddr_in sin, sin_client1;
	//Structure to hold address info

	socklen_client1 = sizeof(sin_client1);
	sin.sin_family = AF_INET;
	sin.sin_port = htonl(7700);
	//Choosing available port to provide
	//process network communication through socket
	//htonl function convertes host (local PC)
	//representation to network representation

	sin.sin_addr.S_un.S_addr = inet_addr("95.180.242.47");
	//Here should be real PUBLIC (white) IP address of PC
	//inet_addr func convertes human repr of IP to net repr

	if (bind(soc, (const sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cerr << WSAGetLastError() << endl;
		//WSAGetLastError func returns code of last error
		//occured in work with sockets

		perror("bind error");
		exit(1);
	}
	//Bind our socket with our address. Now clients can find us

	if (listen(soc, 5) == SOCKET_ERROR)
	{
		perror("listen error");
		exit(1);
	}
	//Listenning socket. Now clients can try to connect to this server.
	//Max lenght of clients queue is 5

	if ((soc_client1 = accept(soc, (sockaddr*)&sin_client1, &socklen_client1)) == INVALID_SOCKET)
	{
		perror("accept error");
		exit(1);
	}
	//Accept next client in queue, create new noaddress socket soc_client1
	//to communicate only with this client (making virtual channel socket),
	//save address info about new client in sockaddr_in struct obj sin_client1

	recv(soc_client1, buf, 1000, 0);
	//Recieve message from client1. Can set diff flags!!!

	cout << buf << endl;
	send(soc_client1, "You talk to BIG BOSS", 21, 0);
	//Send message to client1. Can set diff flags!!!

	//shutdown(soc_client1, SD_BOTH);
	//Immediately interrupt recieving and sending messages

	closesocket(soc_client1);
	//Close socket after all operations end in TCP connections.
	//Immediately close socket in UDP connections

	//shutdown(soc, SD_BOTH);
	closesocket(soc);
	WSACleanup();
	//The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll)

	return 0;
}