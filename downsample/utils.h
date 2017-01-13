#ifndef _DOWNSAMPLE_UTILS_H_
#define _DOWNSAMPLE_UTILS_H_

#include <vector>
#include "histogram.h"

class Utils{
public:
	static void print(std::string name, unsigned int* a, size_t size);
	static void print(std::string name, std::vector<unsigned int> v);
	static void print(std::string name, Histogram* h, size_t size);

	static void split(std::string line, std::vector<unsigned int> &numbers);
};

#endif