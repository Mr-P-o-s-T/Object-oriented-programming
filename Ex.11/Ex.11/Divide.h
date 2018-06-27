#pragma once
#include "Operator.h"

class Divide : public Operator<2> {
public:
	Divide() = default;
	~Divide() = default;
private:
	float getValue() {
		return operands[0]->GetValue() / operands[1]->GetValue();
	}
};
