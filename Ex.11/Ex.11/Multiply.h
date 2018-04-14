#pragma once
#include "Operator.h"

class Multiply : public Operator<2> {
public:
	Multiply() = default;
	~Multiply() = default;

	float getValue() {
		return operands[0]->getValue() * operands[1]->getValue();
	}
};
