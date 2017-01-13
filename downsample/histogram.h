#ifndef _DOWNSAMPLE_HISTOGRAM_H_
#define _DOWNSAMPLE_HISTOGRAM_H_

#include <boost/unordered/unordered_map.hpp>

class Histogram {
public:
	Histogram();
	~Histogram();
	void increment(unsigned int pixel);
	unsigned int mode();
	void merge(const Histogram& other);
	std::string to_str() const;
private:
	void increment_by(unsigned int pixel, unsigned int delta);
	typedef boost::unordered_map<unsigned int, unsigned int> buckets_type;
	buckets_type buckets;
};

#endif