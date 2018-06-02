#pragma once
#include "Bucket.h"

class Sorter {
public:
	Sorter() = default;
	virtual ~Sorter() = default;

	void Sort(Bucket &vault) {
		data = &vault.GiveData();
		sortMethod();
	}
protected:
	std::vector<int> *data;
private:
	virtual void sortMethod() = 0;
};
