#include "Settings.h"
#include "BucketSorter.h"
#include "CombSorter.h"
using namespace std;

void BucketSorter::sortMethod() {
	min = data->front(), max = min;
	for (size_t i = 0; i < data->size(); i++) {
		if ((*data)[i] < min) min = (*data)[i];
		else if ((*data)[i] > max) max = (*data)[i];
	}
	if (min != max) {
		max += 1;
		Bucket *buckets = new Bucket[k];

		for (size_t i = 0; i < data->size(); i++) {
			buckets[getIndex((*data)[i])].AddData((*data)[i]);
		}

		for (size_t i = 0; i < k; i++) {
			Sorter *sorter;
			if (buckets[i].GiveData().size() <= SORT_METHOD_SWITCHER_NUM) sorter = new CombSorter();
			else sorter = new BucketSorter(k);
			sorter->Sort(buckets[i]);
			delete sorter;
		}

		vector<int> res;
		for (size_t i = 0; i < k; i++) {
			size_t nI = buckets[i].GiveData().size();
			for (size_t j = 0; j < nI; j++) res.push_back(buckets[i].GiveData()[j]);
		}

		data->clear();
		swap(*data, res);

		delete[] buckets;
	}
}
