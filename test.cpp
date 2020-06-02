#include "Game.h"

#include "Loading.h"
#include "Intro.h"
#include "Menu.h"
#include "Proc.h"
#include "Ending.h"

#include<process.h>

#pragma comment(lib, "ws2_32.lib")


char* getHttpHeader(const char* url, int port)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return NULL;

	struct hostent* host_entry = gethostbyname(url);
	if (host_entry == NULL)
		return NULL;

	int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == -1)
		return NULL;

	struct sockaddr_in server_addr;
	memset(&server_addr, 0x00, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	memcpy((void*)&server_addr.sin_addr, (void*)(host_entry->h_addr), sizeof(host_entry->h_addr));

	if (connect(client_socket, (struct sockaddr*) & server_addr, sizeof(server_addr)) == -1)
		return NULL;

	const char* s = "HEAD / HTTP/1.0\r\n\r\n";// only http head
	send(client_socket, s, strlen(s), 0);

	char* buf = (char*)calloc(sizeof(char), 10000);
	int bufLen = 0;
	while (1)
	{
		char b[10000];
		size_t len = recv(client_socket, b, 10000, 0);
		if (len > 0)
		{
			memcpy(&buf[bufLen], b, len);
			bufLen += len;
		}
		else
			break;
	}
	return buf;
}


unsigned int __stdcall threadPrint(void* parm)
{
	char* buf = getHttpHeader("www.ncsoft.com", 80);
	saveFile("thread.tex", buf, 10000);

	free(buf);

	int n = (int)parm;
	_endthreadex(n);

	return 0;

}




void loadGame()
{
	unsigned int id;
	HANDLE hand1 = (HANDLE)_beginthreadex(NULL, 0, threadPrint, (void*)0, NULL, &id);





char* getHttpheader(const char* url, int part)
{
		struct hostent* host_entry = gethostbyname(url);
		if (host_entry == NULL)
			return NULL;

		int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (client_socket == -1)
			return NULL;


		struct sockaddr_in sever_addr;
		memset(&sever_addr, 0x00, sizeof(sever_addr));

		sever_addr.sin_family = AF_INET;
		sever_addr.sin_port = htons(part);

		memcpy(&sever_addr.sin_addr, (void*)(host_entry->h_addr), sizeof(host_entry->h_addr));

}

///thread test.