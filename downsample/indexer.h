#ifndef _DOWNSAMPLE_INDEXER_H_
#define _DOWNSAMPLE_INDEXER_H_

#include <vector>
using namespace std;
class Indexer{
public:
	Indexer(vector<unsigned int> values) : values(values){}
	typedef vector<unsigned int>::const_iterator indexer_iterator;
	indexer_iterator begin()const { return this->values.begin(); };
	indexer_iterator end()const{ return this->values.end(); };
private:
	vector<unsigned int> values;
};

#endif