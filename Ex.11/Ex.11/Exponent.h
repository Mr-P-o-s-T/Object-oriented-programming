#pragma once
#include "Operator.h"
#include <cmath>

class Exponent : public Operator<2> {
public:
	Exponent() = default;
	~Exponent() = default;

	float getValue() {
		return pow(operands[0]->getValue(), operands[1]->getValue());
	}
};
