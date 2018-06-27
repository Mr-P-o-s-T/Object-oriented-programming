#pragma once
#include "Operator.h"

class Plus : public Operator<2> {
public:
	Plus() = default;
	~Plus() = default;
private:
	float getValue() {
		return operands[0]->GetValue() + operands[1]->GetValue();
	}
};
