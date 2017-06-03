#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<iostream>
#include<WS2tcpip.h>
using namespace std;
SOCKET Connect;
SOCKET *Connections;
SOCKET ListenSocket;
#define PORT "7770"

int ClientCount = 0;
void SendMessageToClient(int ID)
{
	char *buffer = new char[1024];
	for (;; Sleep(75))
	{
		memset(buffer, 0, sizeof(buffer));
		if (recv(Connections[ID], buffer, 1024, NULL))
		{
			for (int i = 0; i <= ClientCount; i++)
				send(Connections[i], buffer, strlen(buffer), NULL);
		}
	}
	delete buffer;
}
int main()
{
	setlocale(LC_ALL, "russian");
	WSAData Wsadata;
	int res = WSAStartup(MAKEWORD(2, 2), &Wsadata);
	if (res != 0){return 0;}

	struct addrinfo hints;
	struct addrinfo * result;

	Connections = (SOCKET*)calloc(64, sizeof(SOCKET));
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	int iResult;
	iResult = getaddrinfo(NULL, PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	iResult = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	listen(ListenSocket, SOMAXCONN);
	freeaddrinfo(result);

	printf("ready\n");
	char m_connect[] = "Connected";

	for (;; Sleep(75))
	{
		if (Connect = accept(ListenSocket, NULL, NULL))
		{
			printf("Client connect...\n");
			char b[1024];
			//printf("%d\n", recv(Connect, b, strlen(b), 0));
			Connections[ClientCount] = Connect;
			send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);
			recv(Connections[ClientCount], b, 1024, 0);
			
			//int s = atoi(b);
			//printf("%d\n", s);
			send(Connections[ClientCount], b, 1024, 0);
			//char key[] = "123456";
			//int ss = atoi(key);
			//if (s == ss) { 
				//printf("yes\n");
				//send(Connections[ClientCount], "key correct", 11, NULL);
			//}
			//else { 
				//printf("no\n");
				//send(Connections[ClientCount], "wrong key", 9, NULL);
			
			//}
			/*for (int i = 0; i < strlen(b); i++)
			{
				printf("%c    %c\n", b[i], key[i]);
				if (b[i] == key[i]) printf("yes\n");
				else printf("no\n");
			}*/
			//send(Connections[ClientCount], "hello\n", 5, NULL);
			//printf("%s", recv(Connections[ClientCount], b, strlen(b), 0));
			ClientCount++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (PVOID)(ClientCount - 1), NULL, NULL);
		}
	}
	return 1;
}
