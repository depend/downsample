#ifndef _DOWNSAMPLE_PROTON_H_
#define _DOWNSAMPLE_PROTON_H_

#include <vector>
#include "utils.h"
#include <boost/shared_array.hpp>
#include <zi/concurrency/concurrency.hpp>

using namespace std;

class Proton{
public:
	Proton(size_t data_size, vector<unsigned int> dimensions, unsigned int interval);
public:
	template <typename FUNC>
	void fold_apply(FUNC apply) {
		size_t anchors_size = 1;
		for (int i = 0; i < dimensions.size(); i++)
			anchors_size *= dimensions[i] / interval;

		boost::shared_array<unsigned int> anchors(new unsigned int[anchors_size]);
		anchors[0] = 0;
		this->expand(anchors.get(), anchors_size, this->interval, 0);
		//Utils::print("anchors:", anchors.get(), anchors_size);
		//cout << "cells:" << endl;

		size_t cell_size = 1 << dimensions.size();
		for (int i = 0; i < anchors_size; i++){
			boost::shared_array<unsigned int> cell(new unsigned int[cell_size]);
			cell[0] = anchors[i];
			this->expand(cell.get(), cell_size, 1, 1);
			apply(i, cell.get(), cell_size);
		}
	}
private:
	void chunk(vector<unsigned int> &tails, vector<unsigned int> &ends, vector<unsigned int> &steps, unsigned int interval, unsigned int max_steps);
	void expand(unsigned int* indices, size_t indices_size, unsigned int interval, unsigned int max_steps);
private:
	size_t data_size;
	size_t dimensions_size;
	unsigned int interval;
	vector<unsigned int> dimensions;
};

#endif