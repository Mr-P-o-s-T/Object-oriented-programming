#pragma once
#include "Operator.h"
#include <cmath>

class Exponent : public Operator<2> {
public:
	Exponent() = default;
	~Exponent() = default;
private:
	float getValue() {
		return pow(operands[0]->GetValue(), operands[1]->GetValue());
	}
};
