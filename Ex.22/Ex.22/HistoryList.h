#pragma once
#include "IObserver.h"
#include <vector>

class HistoryList : public IObserver<double> {
public:
	HistoryList() {}
	~HistoryList() {}

	void updated(double &data) {
		history.push_back(data);
	}

	const std::vector<double> &getHistory() {
		return history;
	}
private:
	std::vector<double> history;
};
