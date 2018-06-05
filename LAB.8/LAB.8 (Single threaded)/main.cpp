// main file
#include "BucketSorter.h"
#include <iostream>
#include <ctime>
using namespace std;

vector<int> getRandomVector(size_t size) {
	vector<int> res;
	res.reserve(size);
	for (size_t i = 0; i < size; i++) {
		res.push_back(rand());
	}
	return res;
}

int main() {
	vector<int> data(getRandomVector(100000));
	Bucket bucket(data);
	Sorter *srtr = new BucketSorter(5);
	clock_t start = clock();
	srtr->Sort(bucket);
	clock_t end = clock();
	cout << "Sorting time: " << end - start << "ms\n";
	delete srtr;
	system("pause");
	return 0;
}