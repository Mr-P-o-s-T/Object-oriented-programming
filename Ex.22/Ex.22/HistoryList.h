#pragma once
#include "IObserver.h"
#include <vector>

class HistoryList : public IObserver<std::vector<double>> {
public:
	HistoryList() {}
	~HistoryList() {}

	void updated(double &data) {
		history.push_back(data);
	}

	const std::vector<double> &getResult() {
		return history;
	}
private:
	std::vector<double> history;
};
