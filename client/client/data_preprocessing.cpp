#include "data_preprocessing.h"
#include <mutex>

#include <mutex>
#include <chrono>
#include <thread>

#include <iostream>


static std::mutex rawDataQMtx; 

void data_preprocessor(std::list<std::vector<uint16_t>> &rawDataQueue, std::list<std::vector<int>>& tracesQueue)
{
	auto start_time = std::chrono::system_clock::now();
	//auto end_time = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();
	for (int i = 0; (std::chrono::system_clock::now() - start_time).count() < 100000; i++) {
		if (rawDataQueue.size() != 0) {
			rawDataQMtx.lock();
			std::cout << "size = " << rawDataQueue.size() << "; pop from queue\n";
			rawDataQueue.pop_back();
			rawDataQMtx.unlock();
			start_time = std::chrono::system_clock::now();
		}
	}
}
