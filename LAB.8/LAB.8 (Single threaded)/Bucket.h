#pragma once
#include <vector>

class Bucket {
public:
	Bucket() = default;
	Bucket(std::vector<int> &values) {
		swap(values, data);
	}
	~Bucket() = default;

	void AddData(int &newData) {
		data.push_back(newData);
	}
	std::vector<int> &GiveData() {
		return data;
	}
private:
	std::vector<int> data;
};
