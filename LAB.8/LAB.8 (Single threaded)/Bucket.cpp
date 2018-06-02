#include "Bucket.h"
using namespace std;

Bucket::Bucket() {

}

Bucket::~Bucket() {

}

void Bucket::combSort() {
	{
		double factor = 1.2473309;
		double di = data.size() - 1;
		while (di >= 1) {
			for (int i = 0; i + di < data.size(); ++i) 
				if (data[i] > data[i + di]) swap(data[i], data[i + di]);
			di /= factor;
		}
	}
	for (int i = 0; i < data.size() - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < data.size() - i - 1; j++) 
			if (data[j] > data[j + 1]) {
				swap(data[j], data[j + 1]);
				swapped = true;
			}
		if (!swapped) break;
	}
}
