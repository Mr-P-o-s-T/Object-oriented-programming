#pragma once
#include "Operator.h"

class Minus : public Operator<2> {
public:
	Minus() = default;
	~Minus() = default;
private:
	float getValue() {
		return operands[0]->GetValue() - operands[1]->GetValue();
	}
};
