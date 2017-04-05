#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<iostream>
#include<WS2tcpip.h>
#include<stdio.h>
#include<string>
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
	string s = "";
	printf("Welcome to the chat server, Please enter the license key\n");
	getline(cin, s);
	cout << s+"\n";
	if (s == "hhh") cout << "yyy\n";
	else cout << "no\n";
	
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
	char m_connect[] = "Connecting";

	for (;; Sleep(75))
	{
		if (Connect = accept(ListenSocket, NULL, NULL))
		{
			printf("Client connecting...\n");
			char b[1024];
			send(Connect, m_connect, strlen(m_connect), NULL);
			recv(Connect, b, 1024, 0);
			printf("%s\n", b);//выводим пароль

			int f1 = 0, f2 = 0, f3 = 0;
			for (int i = 0; i < 1024; i++) {
				if (b[i] == 'N') f1 = 1;
				if (b[i] == '5') f2 = 1;
				if (b[i] == 'z') f3 = 1;
			}
			int sum = f1 + f2 + f3;
			printf("%d\n", sum);
			if (sum == 3) {
				printf("yes\n");
				send(Connect, "key correct", 12, NULL);
				Connections[ClientCount] = Connect;
			}
			else {
				printf("no\n");
				send(Connect, "wrong  key ", 12, NULL);
			}

			ClientCount++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (PVOID)(ClientCount - 1), NULL, NULL);
		}
	}
	return 1;
}
