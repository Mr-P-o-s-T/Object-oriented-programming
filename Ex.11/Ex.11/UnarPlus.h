#pragma once
#include "Operator.h"

class UnarPlus : public Operator<1> {
public:
	UnarPlus() = default;
	~UnarPlus() = default;
private:
	float getValue() {
		return operands[0]->GetValue();
	}
};
