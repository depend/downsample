#include "common.h"
#include "proton.h"
#include "utils.h"

Proton::Proton(size_t data_size, vector<unsigned int> dimensions, unsigned int interval) :
data_size(data_size),
dimensions(dimensions),
dimensions_size(dimensions.size()),
interval(interval) {
}

void Proton::chunk(vector<unsigned int> &tails, vector<unsigned int> &ends, vector<unsigned int> &steps, unsigned int interval, unsigned int max_steps){
	unsigned int step = interval;
	unsigned int size = 1;
	unsigned int tail = 1;
	for (int i = 0; i < this->dimensions_size; i++) {
		ends.push_back(size*this->dimensions[i]);
		steps.push_back(step);
		size *= this->dimensions[i];
		tail = max_steps == 0 ? size / step * tail : tail + max_steps*(1 << i);
		tails.push_back(tail);
		step *= this->dimensions[i];
	}

	//Utils::print(this->dimensions);
	//Utils::print(tails);
	//Utils::print(ends);
	//Utils::print(steps);
}

void translate(unsigned int* indices, unsigned int from, unsigned int tail, unsigned int batch, unsigned int step){
	int to = from + tail * batch;
	//cout << indices[from] << ":" << from << " to " << to << endl;
	indices[to] = indices[from] + batch*step;
}

void Proton::expand(unsigned int* indices, size_t indices_size, unsigned int interval, unsigned int max_steps) {
	vector<unsigned int> tails = { 1 };
	vector<unsigned int> ends;
	vector<unsigned int> steps;
	this->chunk(tails, ends, steps, interval, max_steps);

	zi::task_manager::deque tm(MAX_CONCURRENCY);
	tm.start();

	for (int d = 0; d < this->dimensions_size; d++) {
		for (int i = 0; i < tails[d]; i++) {
			unsigned int batches = max_steps == 0 ? ends[d] / steps[d] : max_steps + 1;
			for (int k = 1; k < batches; k++) {
				//translate(indices, i, tails[d], k, steps[d]);
				tm.insert(zi::run_fn(zi::bind(&translate, indices, i, tails[d], k, steps[d])));
			}
		}
	}

	tm.join();
}