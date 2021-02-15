#include "TcpClient.h"

tcpClient::tcpClient() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}
	else {
		printf("WSAStartup not failed: %d\n", iResult);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(/*argv[1]*/addr, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
	}
	else {
		printf("getaddrinfo ok: %d\n", iResult);
	}

	ConnectSocket = INVALID_SOCKET;

	ptr = result;

	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}
	else {
		printf("No errors\n");
	}

	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("Socket connect error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
	}
	else {
		printf("Connected!\n");
	}


}

int tcpClient::tcpSend(const char* _sendBuf, size_t _buffLen) {
	iResult = send(ConnectSocket, _sendBuf, _buffLen, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		return iResult;
	}
	else {
		printf("Sent ok\n");
		printf("Bytes Sent: %ld\n", iResult);
	}
	return iResult;
}

int tcpClient::tcpReceive(size_t _recvbuflen) {
	//do {
	iResult = recv(ConnectSocket, recvbuf, _recvbuflen, 0);
	printf("iResult == %d\n", iResult);
	if (iResult > 0) {
		printf("Bytes received: %d\n", iResult);
	}
	else {
		if (iResult == 0) {
			printf("Connection closed\n");
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			iResult = -1;
		}
	}
	//} while (iResult > 0);
	return iResult;
}

tcpClient::~tcpClient() {
	closesocket(ConnectSocket);
	WSACleanup();
}
