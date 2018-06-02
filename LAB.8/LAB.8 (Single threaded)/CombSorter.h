#pragma once
#include "Sorter.h"

class CombSorter : public Sorter {
public:
	CombSorter() : Sorter() {}
	~CombSorter() = default;
private:
	void sortMethod();
};
