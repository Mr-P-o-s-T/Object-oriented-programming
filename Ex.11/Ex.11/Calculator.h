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
		if (tmp) {
			float res = tmp->GetValue();
			delete tmp;
			return res;
		}
		else throw std::exception("Empty expression string...");
	}
private:
	ITerm *buildSubtree(std::string &expression);

	std::string getSummand(std::string &expression);
	std::string getFactor(std::string &expression);
	std::string getExpFormula(std::string &expression);

	ITerm *summand(std::string &expression);
	ITerm *factor(std::string &expression);
	ITerm *expFormula(std::string &expression);
	ITerm *item(std::string &expression);

	float getNumber(std::string &expression);
};
