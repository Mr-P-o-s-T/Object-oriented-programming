#pragma once
#include "ITerm.h"
#include <vector>
#include <exception>

template <size_t NArity>
class Operator : public ITerm {
public:
	Operator() = default;

	void addSubterm(ITerm *t) {
		operands.push_back(t);
	}

	void deleteSubterm(size_t index) {
		delete operands[index];
		operands.erase(operands.begin() + index);
	}

	void deleteSubterms(size_t indexFrom = 0, size_t indexTo = NArity - 1) {
		for (size_t i = indexFrom; i <= indexTo; i++) delete operands[i];
		operands.erase(operands.begin() + indexFrom, operands.begin() + indexTo);
	}

	virtual float getValue() = 0;

	virtual ~Operator() {
		for (size_t i = 0; i < operands.size(); i++) delete operands[i];
	}
private:
	std::vector<ITerm *> operands;
};
