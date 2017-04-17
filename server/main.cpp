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
#define PORT "631"

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
	int ff0 = 0, ff1 = 0, ff2 = 0, ff3 = 0, ff4 = 0, ff5 = 0, ff6 = 0, ff7 = 0, ff8 = 0, ff9 = 0;
	if (48 <= int(s[0]) && int(s[0]) <= 57)ff0 = 1;
	if (97 <= int(s[1]) && int(s[1]) <= 122)ff1 = 1;
	if (97 <= int(s[2]) && int(s[2]) <= 122)ff2 = 1;
	if (33 <= int(s[3]) && int(s[3]) <= 39)ff3 = 1;
	if (65 <= int(s[4]) && int(s[4]) <= 90)ff4 = 1;
	if (33 <= int(s[5]) && int(s[5]) <= 39)ff5 = 1;
	if (48 <= int(s[6]) && int(s[6]) <= 57)ff6 = 1;
	if (65 <= int(s[7]) && int(s[7]) <= 90)ff7 = 1;
	if (48 <= int(s[8]) && int(s[8]) <= 57)ff8 = 1;
	if (48 <= int(s[9]) && int(s[9]) <= 57)ff9 = 1;
	int f00f = ff0 + ff1 + ff2 + ff3 + ff4 + ff5 + ff6 + ff7 + ff8 + ff9;
	int f01f = int(s[0]) + int(s[6]) + int(s[8]) + int(s[9]) - 192;

	if (f00f = 10 && f01f == 15) {

		cout << "key correct\n";

		setlocale(LC_ALL, "russian");
		WSAData Wsadata;
		int res = WSAStartup(MAKEWORD(2, 2), &Wsadata);
		if (res != 0) { return 0; }

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
				printf("Line %d\n", strlen(b));



				int f0 = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0, f6 = 0, f7 = 0, f8 = 0, f9 = 0;
				if (97 <= int(b[0]) && int(b[0]) <= 122)f0 = 1;
				if (48 <= int(b[1]) && int(b[1]) <= 57) f1 = 1;
				if (65 <= int(b[2]) && int(b[2]) <= 90) f2 = 1;
				if (65 <= int(b[3]) && int(b[3]) <= 90) f3 = 1;
				if (97 <= int(b[4]) && int(b[4]) <= 122) f4 = 1;
				if (33 <= int(b[5]) && int(b[5]) <= 39) f5 = 1;
				if (48 <= int(b[6]) && int(b[6]) <= 57) f6 = 1;
				if (48 <= int(b[7]) && int(b[7]) <= 57) f7 = 1;
				if (97 <= int(b[8]) && int(b[8]) <= 122) f8 = 1;
				if (65 <= int(b[9]) && int(b[9]) <= 90) f9 = 1;

				int f00 = f0 + f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8 + f9;
				int f01 = int(b[1]) + int(b[6]) + int(b[7]) - 144;


				printf("f00 f01 %d %d\n", f00, f01);
				if (f00 == 10 && f01 == 20) {
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
	}
	else {
		cout << "no\n";
		cout << "key wrong!!!\n";
		system("pause");
	}

	return 1;
}
