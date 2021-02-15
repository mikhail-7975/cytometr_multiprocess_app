#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#define DEFAULT_BUFLEN 512
#pragma comment(lib, "Ws2_32.lib")


class tcpClient {
	WSADATA wsaData;
	int iResult;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	char addr[15] = "192.168.33.178";
	char DEFAULT_PORT[5] = "9090";
	SOCKET ConnectSocket;

	const char* sendbuf = "this is a test";
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];

public:
	tcpClient();
	int tcpSend(const char* _sendBuf, size_t _buffLen);
	int tcpReceive(size_t _recvbuflen);
	~tcpClient();
};