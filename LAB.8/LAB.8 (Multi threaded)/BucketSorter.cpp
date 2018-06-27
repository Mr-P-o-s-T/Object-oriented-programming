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


		for (size_t i = 0; i < k; i++) {
			buckets[i].setNewThread(new thread(&BucketSorter::multiSplitting, this, buckets));
		}

		for (size_t i = 0; i < k; i++) buckets[i].finalizeCurrThread();

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

void BucketSorter::multiSplitting(Bucket * buckets) {
	Bucket *owner = &buckets[0];
	for (size_t i = 0; i < k; i++) {
		if (buckets[i].isCurrThread(std::this_thread::get_id())) {
			owner = &buckets[i];
			break;
		}
	}

	for (size_t i = 0; i < data->size(); i++) {
		if (&buckets[getIndex((*data)[i])] == owner) owner->AddData((*data)[i]);
	}

	Sorter *sorter;
	if (owner->GiveData().size() <= SORT_METHOD_SWITCHER_NUM) sorter = new CombSorter();
	else sorter = new BucketSorter(k);
	sorter->Sort(*owner);
	delete sorter;
}
