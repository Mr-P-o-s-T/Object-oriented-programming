#pragma once
#include "Sorter.h"
class BucketSorter : public Sorter {
public:
	BucketSorter(size_t k) : Sorter(), k(k) {}
	~BucketSorter() = default;
private:
	int min, max;
	size_t k;
	void sortMethod();
	size_t getIndex(const int &value) {
		return (size_t) (k * ((double) value - min) / (max - min));
	}
};
