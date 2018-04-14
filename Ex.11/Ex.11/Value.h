#pragma once
#include "ITerm.h"

class Value : public ITerm {
public:
	Value(float value) { this->value = value; }
	~Value() = default;

	float getValue() { return value; }
private:
	float value;
};

