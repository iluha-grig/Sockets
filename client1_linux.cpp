#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

using namespace std;

int main()
{
	char buf[1000], myhost[100];
	int soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soc < 0)
	{
		perror("socket error");
		exit(1);
	}
	gethostname(myhost, 100);
	hostent *myaddr = gethostbyname(myhost);
	//Get all info about my host

	sockaddr_in sin, sin_server;
	sin.sin_family = AF_INET;
	sin.sin_port = htonl(6969);
	memcpy(&sin.sin_addr, myaddr->h_addr_list[0], myaddr->h_length);
	//This host address info

	if (bind(soc, (const sockaddr *)&sin, sizeof(sin)) < 0)
	{
		perror("bind error");
		exit(1);
	}
	sin_server.sin_family = AF_INET;
	sin_server.sin_port = htonl(7700);
	sin_server.sin_addr.s_addr = inet_addr("95.180.242.47");
	//Server to connect address info

	if (connect(soc, (const sockaddr *)&sin_server, sizeof(sin_server)) < 0)
	{
		perror("connect error");
		exit(1);
	}
	//Connecting to server, waiting to be accepted

	send(soc, "Hello, the most powerfull PC in this house!", 100, 0);
	recv(soc, buf, 1000, 0);
	cout << buf << endl;
	shutdown(soc, SHUT_RDWR);
	//In client prog we can easily do shutdown,
	//because we know when we stop communication

	close(soc);
	return 0;
}
