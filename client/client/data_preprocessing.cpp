#include "data_preprocessing.h"
#include <mutex>

#include <mutex>
#include <chrono>
#include <thread>

#include <iostream>


static std::mutex rawDataQMtx; 

void data_preprocessor(std::list<std::vector<uint16_t>> &rawDataQueue, std::list<std::vector<int>>& tracesQueue)
{
	for (int i = 0; ; i++) {
		
		if (rawDataQueue.size() != 0) {
			rawDataQMtx.lock();
			std::cout <<"size = " << rawDataQueue.size() << "; pop from queue" << std::endl;
			rawDataQueue.pop_back();
			rawDataQMtx.unlock();
		}
	}
}
