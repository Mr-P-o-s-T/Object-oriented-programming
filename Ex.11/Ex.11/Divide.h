#pragma once
#include "Operator.h"

class Divide : public Operator<2> {
public:
	Divide() = default;
	~Divide() = default;

	float getValue() {
		return operands[0]->getValue() / operands[1]->getValue();
	}
};
