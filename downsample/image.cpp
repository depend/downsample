#include "image.h"
#include "utils.h"
#include "proton.h"
#include <iostream>
#include <fstream>
#include <array>
#include <limits.h>
#include <zi/concurrency/concurrency.hpp>
using namespace std;

size_t Image::get_data_size(){
	size_t size = 1;
	for (int i = 0; i < this->dimensions.size(); i++)
		size *= this->dimensions[i];
	return size;
}

void Image::load(string const& path){
	cout << "load image from file: " << path << endl;

	ifstream infile(path);
	string line;

	// read dimensions
	getline(infile, line);
	vector<unsigned int> shape;
	Utils::split(line, shape);
	for (int i = 0; i < shape.size(); i++){
		this->dimensions.push_back(2 << (shape[i] - 1));
	}

	reverse(this->dimensions.begin(), this->dimensions.end());

	//Utils::print(this->dimensions);

	size_t data_size = this->get_data_size();
	// read data
	this->data.reset(new unsigned int[data_size]);
	unsigned int i = 0;
	while (getline(infile, line)){
		vector<unsigned int> pixels;
		Utils::split(line, pixels);
		for (int x = 0; x < pixels.size(); x++){
			this->data[i++] = pixels[x];
		}
	}

	// allocate histograms
	this->histogram_size = data_size / (2 << this->dimensions.size() - 1);
	this->histograms.reset(new Histogram[this->histogram_size]);
	this->update_histograms();
	//cout << "size: " << data_size << "; histogram_size: " << this->histogram_size << endl;
}

Image::Image(Histogram* histograms, size_t histograms_size, vector<unsigned int> dimensions){
	//cout << "create image " << this->id << endl;
	this->dimensions = dimensions;

	// data
	this->data.reset(new unsigned int[histograms_size]);
	for (int i = 0; i < histograms_size; i++){
		this->data[i] = histograms[i].mode();
	}

	// update histograms
	this->merge_histograms(histograms, histograms_size);
	//cout << "merged histograms:" << endl;
	//Utils::print(this->histograms, this->histogram_size);
}

void Image::merge_histograms(Histogram* histograms, size_t histograms_size){	
	//cout << "merging histograms..." << endl;
	this->histogram_size = histograms_size / (2 << this->dimensions.size() - 1);

	if (this->histogram_size == 0){
		return;
	}

	this->histograms.reset(new Histogram[this->histogram_size]);

	Proton p(this->get_data_size(), this->dimensions, 2);
	p.fold_apply([this, histograms](unsigned int hist_index, unsigned int* cell, unsigned int cell_size) {
		//Utils::print("merge cell: ", cell, cell_size);
		for (int i = 0; i < cell_size; i++) {
			this->histograms[hist_index].merge(histograms[cell[i]]);
		}
	});
}

Image::Image(string const& path) {
	//cout << "create image from file " << this->id << endl;
	load(path);
}

Image::~Image(){
}

void Image::print(){
	Utils::print("dimension: ", this->dimensions);
	Utils::print("image: ", this->data.get(), this->get_data_size());
}

void Image::update_histograms() {
	Proton p(this->get_data_size(), this->dimensions, 2);
	p.fold_apply([this](unsigned int hist_index, unsigned int* cell, unsigned int cell_size) {
		//Utils::print("cell: ", cell, cell_size);
		for (int i = 0; i < cell_size; i++) {
			//cout << "hist " << hist_index << ":" << this->data[cube[i]] << endl;
			this->histograms[hist_index].increment(this->data[cell[i]]);
		}
	});
}

bool Image::can_down_sample(){
	for (int i = 0; i < this->dimensions.size(); i++){
		if (this->dimensions[i] == 1)
			return false;
	}
	return true;
}

Image Image::down_sample(){
	vector<unsigned int> dimensions;
	for (int i = 0; i < this->dimensions.size(); i++){
		dimensions.push_back(this->dimensions[i] >> 1);
	}
	return Image(this->histograms.get(), this->histogram_size, dimensions);
}