#ifndef _DOWNSAMPLE_UTILS_H_
#define _DOWNSAMPLE_UTILS_H_

#include <vector>
#include "histogram.h"

using namespace std;

class Utils{
public:
	static void print(string name, unsigned int* a, size_t size);
	static void print(string name, vector<unsigned int> v);
	static void print(string name, Histogram* h, size_t size);

	static void split(string line, vector<unsigned int> &numbers);
};

#endif