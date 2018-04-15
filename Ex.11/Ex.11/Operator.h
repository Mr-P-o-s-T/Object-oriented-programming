#pragma once
#include "ITerm.h"
#include <vector>

template <size_t NArity>
class Operator : public ITerm {
public:
	Operator() = default;

	void addSubterm(ITerm *t) {
		if (operands.size() >= NArity) throw std::exception("All operands are already added...");
		operands.push_back(t);
	}

	void deleteSubterm(size_t index) {
		if (index >= NArity) throw std::exception("Operand does not exist...");
		delete operands[index];
		operands.erase(operands.begin() + index);
		
	}

	void deleteSubterms(size_t indexFrom = 0, size_t indexTo = NArity - 1) {
		if ((indexFrom >= NArity) || (indexTo >= NArity)) throw std::exception("Operands does not exist...");
		for (size_t i = indexFrom; i <= indexTo; i++) delete operands[i];
		operands.erase(operands.begin() + indexFrom, operands.begin() + indexTo);
		if (indexTo == NArity - 1) operands.pop_back();
	}

	virtual float getValue() = 0;

	virtual ~Operator() {
		for (size_t i = 0; i < operands.size(); i++) delete operands[i];
	}
protected:
	std::vector<ITerm *> operands;
};
