#pragma once
#include "ObservableDouble.h"
#include "HistoryList.h"

class Sorter : private ObservableDouble, public IObserver<double> {
public:
	Sorter() {
		resList = new HistoryList();
	}
	~Sorter() {
		delete resList;
	}

	void setValue(double newValue) {
		delete resList;
		vault.push_back(newValue);
		sortVault();
		resList = new HistoryList();
		for (size_t i = 0; i < vault.size(); i++) notify(vault[i]);
	}

	void updated(double &data) {
		setValue(data);
	}

	const std::vector<double> &getSortedValues() {
		return resList->getHistory();
	}
private:
	HistoryList *resList = nullptr;
	std::vector<double> vault;

	void sortVault() {
		qsort(vault.data(), vault.size(), sizeof(double), [](const void *a, const void *b) -> int {
			return *(const double *)a - *(const double *)b;
		});
	}
};
