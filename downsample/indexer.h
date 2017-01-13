#ifndef _DOWNSAMPLE_INDEXER_H_
#define _DOWNSAMPLE_INDEXER_H_

#include <vector>

class Indexer{
public:
	Indexer(std::vector<unsigned int> values) : values(values){}
	typedef std::vector<unsigned int>::const_iterator indexer_iterator;
	indexer_iterator begin()const { return this->values.begin(); };
	indexer_iterator end()const{ return this->values.end(); };
private:
	std::vector<unsigned int> values;
};

#endif