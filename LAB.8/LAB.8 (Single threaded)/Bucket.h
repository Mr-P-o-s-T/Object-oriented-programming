#pragma once
#include <vector>

class Bucket {
public:
	Bucket();
	~Bucket();
private:
	std::vector<int> data;

	void combSort();
};
