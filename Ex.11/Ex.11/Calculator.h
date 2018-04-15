#pragma once
#include "Value.h"
#include "Operations.h"
#include <string>

class Calculator {
public:
	Calculator() = default;
	~Calculator() = default;

	float Parser9000(std::string expression) {
		ITerm *tmp = buildSubtree(expression);
		float res = tmp->getValue();
		delete tmp;
	}
private:
	ITerm *buildSubtree(std::string &expression);

	std::string getSummand(std::string &expression);
	std::string getFactor(std::string &expression);

	float getNumber(std::string &expression);
};
