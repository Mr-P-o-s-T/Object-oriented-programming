#pragma once
#include "IObservable.h"
#include <vector>

class ObservableDouble : public IObservable<double> {
public:
	ObservableDouble() {}
	virtual ~ObservableDouble() {}

	void addObserver(IObserver<double> &o) {
		observerList.push_back(o);
	}

	void removeObserver(IObserver<double> &o) {
		for (auto item = observerList.begin(); item != observerList.end(); item++)
			if (&*item == &o) {
				observerList.erase(item);
				break;
			}
	}

	virtual void setValue(double newValue) {
		value = newValue;
		notify(value);
	}
protected:
	std::vector<IObserver<double> &> observerList;

	virtual void notify(double &value) {
		for (auto item = observerList.begin(); item != observerList.end(); item++) (*item).updated(value);
	}
private:
	double value;
};
