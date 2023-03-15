#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <WinSock2.h>
#include <iostream>

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);

	if (WSAStartup(DLLVersion, &wsaData)) {
		std::cout << "Starting up error!" << std::endl;
		std::exit(1);
	}

	SOCKADDR_IN addr;
	int size_of_addr = sizeof(addr);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);

	if (!newConnection) {
		std::cout << "Connection error!" << std::endl;
	}
	else { 
		std::cout << "Client succesfully connected!" << std::endl; 
		char msg[256] = "Hello user!";
		send(newConnection, msg, sizeof(msg), NULL);
	}

	return 0;
}