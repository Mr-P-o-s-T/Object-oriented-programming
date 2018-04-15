#pragma once
#include "ITerm.h"

class Value : public ITerm {
public:
	Value(float value) { this->value = value; }
	~Value() = default;

	void addSubterm(ITerm *t) { throw std::exception("Unsupported operation..."); }

	void deleteSubterm(size_t index) { throw std::exception("Unsupported operation..."); }

	void deleteSubterms(size_t indexFrom, size_t indexTo) { throw std::exception("Unsupported operation..."); }

	float GetValue() { return value; }
private:
	float value;
};

