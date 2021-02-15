#include <winsock2.h>
#include <ws2tcpip.h>
//#include <stdio.h>

#include <iostream>
#include <string>
#include <sstream>

#define DEFAULT_BUFLEN 512
#pragma comment(lib, "Ws2_32.lib")

class tcpClient {
	WSADATA wsaData;
	int iResult;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	char addr[10] = "127.0.0.1";
	char DEFAULT_PORT[5] = "9090";
	SOCKET ConnectSocket;

	const char* sendbuf = "this is a test";
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];

public:
	tcpClient() {
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
		} else {
			printf("getaddrinfo ok: %d\n", iResult);
		}

		ConnectSocket = INVALID_SOCKET;
		
		ptr = result;

		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
		} else {
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
		} else {
			printf("Connected!\n");
		}


	}
	
	int tcpSend(const char* _sendBuf, size_t _buffLen) {
		iResult = send(ConnectSocket, _sendBuf, _buffLen, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			return iResult;
		} else{
			printf("Sent ok\n");
			printf("Bytes Sent: %ld\n", iResult);
		}
		return iResult;
	}

	int tcpReceive(size_t _recvbuflen) {
		//do {
			iResult = recv(ConnectSocket, recvbuf, _recvbuflen, 0);
			printf("iResult == %d\n", iResult);
			if (iResult > 0) {
				printf("Bytes received: %d\n", iResult);
			} else {
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

	~tcpClient() {
		closesocket(ConnectSocket);
		WSACleanup();
	}
};

int main() {
	tcpClient client = tcpClient();
	for(int i = 0; i < 1000; i++) {
		printf("%d: \n", i);
		int arr[2000];
		for (int i = 0; i < 2000; ++i) {
			arr[i] = i + 1;
		}
		std::ostringstream s;
		std::string output_str();
		char ststr_arr[2000 * 5];
		s << i;
		for (int _i = 0; _i < 2000; ++_i) {
			s << ' ' << arr[_i];
		}
		//std::cout << s << s
		std::string ostr = s.str();
		client.tcpSend(ostr.c_str(), ostr.length());
		//client.tcpReceive();
		Sleep(10);
	}
	return 0;
}