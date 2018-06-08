#pragma once
#include "ObservableDouble.h"
#include "HistoryList.h"

class Sorter : public ObservableDouble, public IObserver<double> {
public:
	Sorter() {
		
	}
	~Sorter() {}

	void setValue(double newValue) {
		
		notify();
	}

	void updated(double &data) {
		setValue(data);
	}
private:
	HistoryList resList;

	void notify(double &value) {
		for (auto item = observerList.begin(); item != observerList.end(); item++) (*item).updated(value);
	}
};
