#include <iostream>
//#include <string>
#include <sstream>
#include <list>
#include <vector>

#include <thread>
#include <functional>

#include "TcpClient.h"
#include "data_reading.h"
#include "data_preprocessing.h"
#include "data_output.h"
#include "cmd_input.h"

std::list<std::string> inpRawDataQueue; 
std::list<std::vector<int>> tracesQueue;
std::string tcpSendBuf;
std::string tcpRecvBuf;

int main() {

	std::thread reader(data_reader, std::ref(inpRawDataQueue));
	
	std::thread preprocessor(data_preprocessor, std::ref(inpRawDataQueue), std::ref(tracesQueue));
	std::thread outputThread(data_writer, std::ref(tracesQueue));
	std::thread cmdInputThread(cmd_receiver);
	/*
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
	*/

	reader.join();
	preprocessor.join();
	outputThread.join();
	cmdInputThread.join();
	return 0;
}