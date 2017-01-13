// downsample.cpp : Defines the entry point for the console application.
//

#include "image.h"
#include "proton.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[])
{
	//Proton p(32, { 8, 4 }, 2);
	//p.fold_apply([](unsigned int* cell, unsigned int cell_size) {
	//	Utils::print(cell, cell_size);
	//});
	//cout << endl;

	//Proton p1(32, { 8, 4 }, 1);
	//p1.fold_apply([](vector<unsigned int> cell) {
	//	for (int i = 0; i < cell.size(); i++){
	//		cout << cell[i] << " ";
	//	}
	//	cout << endl;
	//});
	//cout << endl;

	//Proton p2(64, { 4, 4, 4 }, 2);
	//p2.fold_apply([](unsigned int* cell, unsigned int cell_size) {
	//	Utils::print(cell, cell_size);
	//});
	//cout << endl;

	if (argc != 2){
		cout << "usage: " << argv[0] << " <filename>\n";
		return 1;
	}		

	//Image original(string("input1"));
	string input(argv[1]);
	Image original(input);
	original.print();
	
	Image img = original;
	while (img.can_down_sample()){
		cout << "press any key to down sample:" << endl;
		img = img.down_sample();
		img.print();
		cin.get();
	}
	cout << "DONE!" << endl;
	cin.get();
	return 0;
}

