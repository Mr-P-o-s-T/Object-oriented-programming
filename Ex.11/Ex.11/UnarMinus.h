#pragma once
#include "Operator.h"

class UnarMinus : public Operator<1> {
public:
	UnarMinus() = default;
	~UnarMinus() = default;
private:
	float getValue() {
		return -(operands[0]->GetValue());
	}
};
