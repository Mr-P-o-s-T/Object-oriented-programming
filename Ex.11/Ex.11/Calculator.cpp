#include "Calculator.h"

ITerm * Calculator::buildSubtree(std::string &expression) {
	if (!expression.empty()) return summand(expression);
	else throw std::exception("Expression string is empty...");
}

std::string Calculator::getSummand(std::string &expression) {
	std::string res;
	bool inBrackets = false, founded = false;
	for ( ; !expression.empty() && !founded; ) {
		switch (expression.front()) {
		case '+': 
		case '-':
			if (!inBrackets) {
				founded = true;
				break;
			}
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case '(': inBrackets = true;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case ')': inBrackets = false;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case ' ': expression.erase(expression.begin());
			break;
		default: res += expression.front();
			expression.erase(expression.begin());
			break;
		}
	}
	return res;
}

std::string Calculator::getFactor(std::string &expression) {
	std::string res;
	bool inBrackets = false, founded = false;
	for (; !expression.empty() && !founded; ) {
		switch (expression.front()) {
		case '*':
		case '/':
			if (!inBrackets) {
				founded = true;
				break;
			}
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case '(': inBrackets = true;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case ')': inBrackets = false;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		default: res += expression.front();
			expression.erase(expression.begin());
			break;
		}
	}
	return res;
}

std::string Calculator::getExpFormula(std::string & expression) {
	std::string res;
	bool inBrackets = false, founded = false;
	for (; !expression.empty() && !founded; ) {
		switch (expression.front()) {
		case '^':
			if (!inBrackets) {
				founded = true;
				break;
			}
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case '(': inBrackets = true;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		case ')': inBrackets = false;
			res += expression.front();
			expression.erase(expression.begin());
			break;
		default: res += expression.front();
			expression.erase(expression.begin());
			break;
		}
	}
	return res;
}

ITerm * Calculator::summand(std::string &expression) {
	ITerm *root;
	std::string newSummand;
	if (expression.front() == '+') {
		root = new UnarPlus;
		expression.erase(expression.begin());
		newSummand = getSummand(expression);
		root->addSubterm(factor(newSummand));
	}
	else if (expression.front() == '-') {
		root = new UnarMinus;
		expression.erase(expression.begin());
		newSummand = getSummand(expression);
		root->addSubterm(factor(newSummand));
	}
	else {
		newSummand = getSummand(expression);
		root = factor(newSummand);
	}
	while (!expression.empty()) {
		{
			ITerm *tmp;
			if (expression.front() == '+') tmp = new Plus;
			else tmp = new Minus;
			tmp->addSubterm(root);
			root = tmp;
			expression.erase(expression.begin());
		}
		newSummand.clear();
		newSummand = getSummand(expression);
		root->addSubterm(factor(newSummand));
	}
	return root;
}

ITerm * Calculator::factor(std::string &expression) {
	std::string newFactor = getFactor(expression);
	ITerm *root = expFormula(newFactor);
	while (!expression.empty()) {
		{
			ITerm *tmp;
			if (expression.front() == '*') tmp = new Multiply;
			else tmp = new Divide;
			tmp->addSubterm(root);
			root = tmp;
			expression.erase(expression.begin());
		}
		newFactor.clear();
		newFactor = getFactor(expression);
		root->addSubterm(expFormula(newFactor));
	}
	return root;
}

ITerm * Calculator::expFormula(std::string &expression) {
	std::string newExpFormula = getExpFormula(expression);
	ITerm *root = item(newExpFormula);
	while (!expression.empty()) {
		{
			ITerm *tmp = new Exponent;			
			tmp->addSubterm(root);
			root = tmp;
			expression.erase(expression.begin());
		}
		newExpFormula.clear();
		newExpFormula = getExpFormula(expression);
		root->addSubterm(item(newExpFormula));
	}
	return root;
}

ITerm * Calculator::item(std::string &expression) {
	switch (expression.front())	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return new Value(getNumber(expression));
	case '(': 
		if (expression.back() != ')') throw std::exception("No close bracket found...");
		expression.erase(expression.begin());
		expression.pop_back();
		return summand(expression);
	case ')': throw std::exception("No open bracket found...");
		break;
	default: throw std::exception("Unsupported symbol...");
		break;
	}
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
