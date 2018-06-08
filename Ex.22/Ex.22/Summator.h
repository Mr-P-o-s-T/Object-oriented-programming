#pragma once
#include "IObserver.h"
class Summator : public IObserver<double> {
public:
	Summator() {}
	~Summator() {}

	void updated(double &data) {
		currSumm += data;
	}

	const double &getResult() {
		return currSumm;
	}
private:
	double currSumm = 0.0;
};
