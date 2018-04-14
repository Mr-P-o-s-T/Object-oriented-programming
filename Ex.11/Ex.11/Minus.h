#pragma once
#include "Operator.h"

class Minus : public Operator<2> {
public:
	Minus() = default;
	~Minus() = default;

	float getValue() {
		return operands[0]->getValue() - operands[1]->getValue();
	}
};
