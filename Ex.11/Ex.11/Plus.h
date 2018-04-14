#pragma once
#include "Operator.h"

class Plus : public Operator<2> {
public:
	Plus() = default;
	~Plus() = default;

	float getValue() {
		return operands[0]->getValue() + operands[1]->getValue();
	}
};
