#include "Calculator.h"

ITerm * Calculator::buildSubtree(std::string &expression) {

	return nullptr;
}

std::string Calculator::getSummand(std::string &expression) {
	std::string res;
	bool inBrackets = false, founded = false;
	for (size_t i = 0; (i < expression.size()) && (!founded); i++) {
		switch (expression[i]) {
		case '+': 
		case '-':
			if (!inBrackets) {
				founded = true;
				break;
			}
			res += expression[i];
			break;
		case '(': inBrackets = true;
			res += expression[i];
			break;
		case ')': inBrackets = false;
			res += expression[i];
			break;
		default:
			res += expression[i];
			break;
		}
	}
	res = expression.substr(0, expression.size() - res.size());
	return res;
}

std::string Calculator::getFactor(std::string & expression) {
	std::string res;
	bool inBrackets = false, founded = false;
	for (size_t i = 0; (i < expression.size()) && (!founded); i++) {
		switch (expression[i]) {
		case '*':
		case '/':
			if (!inBrackets) {
				founded = true;
				break;
			}
			res += expression[i];
			break;
		case '(': inBrackets = true;
			res += expression[i];
			break;
		case ')': inBrackets = false;
			res += expression[i];
			break;
		default:
			res += expression[i];
			break;
		}
	}
	res = expression.substr(0, expression.size() - res.size());
	return res;
}

float Calculator::getNumber(std::string &expression) {
	float res = 0.0f;
	size_t separator = 0;
	for (size_t i = 0; i < expression.size(); i++) {
		if ((expression[i] != '.') || (expression[i] != ',')) {
			res *= 10.0f;
			res += expression[i] - 48;
		}
		else separator = expression.size() - i - 1;
	}
	for ( ; separator > 0; separator--) res /= 10.0f;
	return res;
}
