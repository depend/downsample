#include "utils.h"
#include <iostream>
#include <sstream>

using namespace std;

void Utils::print(string name, unsigned int* a, size_t size){
	cout << name;
	for (int i = 0; i < size; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

void Utils::print(string name, vector<unsigned int> v){
	cout << name;
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

void Utils::print(string name, Histogram* h, size_t size){
	cout << name;
	for (int i = 0; i < size; i++){
		cout << h[i].to_str() << " ";
	}
	cout << endl;
}

void Utils::split(string line, vector<unsigned int> &numbers){
	stringstream ss;
	ss.str(line);
	string item;
	vector<string> elems;
	while (getline(ss, item, ' ')) {
		elems.push_back(item);
	}

	for (int i = 0; i < elems.size(); i++){
		numbers.push_back(stoi(elems[i]));
	}
}
