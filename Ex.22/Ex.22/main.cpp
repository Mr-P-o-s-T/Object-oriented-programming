// main file
#include "Observer.h"
#include <iostream>
using std::cout;
using std::cin;

int main() {
	ObservableDouble a;

	HistoryList history;
	Mean mean;
	Summator summ;
	Sorter sort;

	a.addObserver(history);
	a.addObserver(mean);
	a.addObserver(summ);
	a.addObserver(sort);

	int item;
	do {
		cout << "1. Set new value.\n2. Exit.";
		cin >> item;
		if (!--item) {
			double newValue;
			cout << "Set new value:\n";
			cin >> newValue;
			a.setValue(newValue);
			std::vector<double> res = history.getHistory();
			cout << "History of variable values:\n";
			for (size_t i = 0; i < res.size(); i++) cout << res[i];
			cout << "Arithmetic mean: " << mean.getMean();
			cout << "Summa of all variable values: " << summ.getSumm();
			res.clear();
			res = sort.getSortedValues();
			cout << "Sorted variable values:\n";
			for (size_t i = 0; i < res.size(); i++) cout << res[i];
		}
	} while (item != 1);
	return 0;
}
