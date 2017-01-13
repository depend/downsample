#include "histogram.h"
#include <sstream>

using namespace std;

Histogram::Histogram(){
	//cout << "creating histogram" << endl;
}

Histogram::~Histogram(){
	//cout << "destroy histogram" << endl;
}

void Histogram::increment_by(unsigned int pixel, unsigned int delta){
	auto b = this->buckets.find(pixel);
	if (b == this->buckets.end())
		this->buckets[pixel] = delta;
	else
		this->buckets[pixel] = b->second + delta;
}

void Histogram::increment(unsigned int pixel){
	this->increment_by(pixel, 1);
}

void Histogram::merge(const Histogram& other){
	//cout << this->to_str() << " merge " << other.to_str() << endl;
	for (auto it = other.buckets.begin(); it != other.buckets.end(); it++) {		
		this->increment_by(it->first, it->second);
	}

	//cout << this->to_str() << endl;
}

string Histogram::to_str() const {
	std::ostringstream ss;
	for (auto it = this->buckets.begin(); it != this->buckets.end(); it++){
		ss << it->first << ":" << it->second << ";";
	}
	return ss.str();
}

unsigned int Histogram::mode(){
	unsigned int mode = this->buckets.begin()->first;
	unsigned int max_count = this->buckets.begin()->second;
	for (auto it = this->buckets.begin(); it != this->buckets.end(); it++){
		if (it->second > max_count){
			max_count = it->second;
			mode = it->first;
		}
	}
	return mode;
}