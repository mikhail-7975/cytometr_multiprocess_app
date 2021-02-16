#include "constants.h"
#include "data_reading.h"

#include <sstream>
#include <vector>

#include <mutex>
#include <chrono>
#include <thread>

#include <iostream>

static std::mutex rawDataQMtx; 

void data_reader(std::list<std::vector<uint16_t>> &rawDataQueue)
{
	for (int i = 0; i < 100; i++) {
		uint16_t baseine_input[TRACE_LEN];
		for (int i = 0; i < TRACE_LEN; i++) {
			baseine_input[i] = i + 1;
		}
		char inpStr[TRACE_LEN * TRACE_ELEM_SIZE];
		memcpy(inpStr, baseine_input, TRACE_LEN * TRACE_ELEM_SIZE);
		uint16_t data[TRACE_LEN];
		memcpy(data, inpStr, TRACE_LEN * TRACE_ELEM_SIZE);
		data;
		rawDataQMtx.lock();
		rawDataQueue.push_back(std::vector<uint16_t>(data, data + TRACE_LEN));
		std::cout << "pushed to queue" << std::endl;
		rawDataQMtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
