#include <iostream>
#include <string>
#include <sstream>

#include "TcpClient.h"

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
		std::string ostr = s.str();
		client.tcpSend(ostr.c_str(), ostr.length());
		client.tcpReceive(100);
		//Sleep(10);
	}
	client.tcpReceive(100);
	return 0;
}