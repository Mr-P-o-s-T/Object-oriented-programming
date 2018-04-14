#pragma once
#include "ITerm.h"

class Value : public ITerm {
public:
	Value(float value) { this->value = value; }
	float getValue() { return value; }
	~Value() { }
private:
	float value;
};

