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
void cdfg() {
	if (IsDebuggerPresent()) exit(0);
}
int main()
{
	int x = 5;
	string s = "";
	cdfg();
	printf("Welcome!!!\n");
	getline(cin, s);


	if (s == "bnfryfxytvyfiehf,jnectujlyz") {
		system("CLS");

		setlocale(LC_ALL, "russian");
		WSAData Wsadata;
		int res = WSAStartup(MAKEWORD(2, 2), &Wsadata);
		if (res != 0) { return 0; }

		struct addrinfo hints;
		struct addrinfo * result;
		int lo = 0;
		Connections = (SOCKET*)calloc(64, sizeof(SOCKET));
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_flags = AI_PASSIVE;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		int iResult;
		int height = 650;
		iResult = getaddrinfo(NULL, PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return 1;
		}
		char wr[] = "npfdnhf";
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
		char sw[] = "fcnfyt";
		listen(ListenSocket, SOMAXCONN);
		freeaddrinfo(result);

		printf("ready\n");
		char m_connect[] = "Connecting";
		cdfg();
		for (;; Sleep(75))
		{
			cdfg();
			if (Connect = accept(ListenSocket, NULL, NULL))
			{
				char b[1024];
				x = 5;
				send(Connect, m_connect, strlen(m_connect), NULL);
				recv(Connect, b, 1024, 0);
				
				char sdf[] = "yjdsqltymy";
				for (int i = 0; i < strlen(sdf); i++) {
					if (b[i] != sdf[i]) {
						send(Connect, "wrong  key ", 12, NULL);
						break;
					}
				}
				lo = 0;
				for (int i = 10; i < strlen(sdf) + 6; i++)
				{
					lo += b[i];
				}
				if (lo == height) {
					for (int i = 16; i < 23; i++) {
						if (b[i] != wr[i - 16]) x = x + x ^ 2;
					}
					if (x == 5) {
						send(Connect, "key correct", 12, NULL);
						Connections[ClientCount] = Connect;
					}
					else
					{
						send(Connect, "wrong  key ", 12, NULL);
					}
				}
				else
				{
					send(Connect, "wrong  key ", 12, NULL);
				}
				

				ClientCount++;
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (PVOID)(ClientCount - 1), NULL, NULL);
			}
		}
	}
	else {
		system("CLS");
		cout << "NO!\n";
		system("pause");
	}

	return 1;
}
