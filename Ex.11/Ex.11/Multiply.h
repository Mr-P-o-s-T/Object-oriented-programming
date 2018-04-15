#pragma once
#include "Operator.h"

class Multiply : public Operator<2> {
public:
	Multiply() = default;
	~Multiply() = default;
private:
	float getValue() {
		return operands[0]->GetValue() * operands[1]->GetValue();
	}
};
