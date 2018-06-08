#pragma once
#include "IObserver.h"
class Mean : public IObserver<double> {
public:
	Mean() {}
	~Mean() {}

	void updated(double &data) {
		currMean = ((double)n) / (n + 1) * currMean + data / (n + 1);
		n++;
	}

	const double &getMean() {
		return currMean;
	}
private:
	double currMean = 0.0;
	size_t n = 0;
};
