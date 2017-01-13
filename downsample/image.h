#ifndef _DOWNSAMPLE_IMAGE_H_
#define _DOWNSAMPLE_IMAGE_H_

#include <string>
#include <vector>
#include <array>
#include "common.h"
#include "histogram.h"
#include "indexer.h"
#include <boost/shared_array.hpp>

class Image {
public:	
	Image(std::string const& path);
	Image(Histogram* histograms, size_t histograms_size, std::vector<unsigned int> dimensions);
	~Image();	
	bool can_down_sample();
	Image down_sample();
public:	
	void print();
private:
	void load(std::string const& path);
	void merge_histograms(Histogram* histograms, size_t histograms_size);
	void update_histograms();
	size_t get_data_size();	
private:
	std::vector<unsigned int> dimensions;
	boost::shared_array<unsigned int> data;
	size_t histogram_size;
	boost::shared_array<Histogram> histograms;
};


#endif