#pragma once

class Sorter {
public:
	Sorter();
	virtual ~Sorter();
private:
	virtual void sortMethod(class Bucket &data) = 0;
};
