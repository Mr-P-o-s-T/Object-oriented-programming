#pragma once
#include "Value.h"
#include "Operations.h"
#include <string>

class Calculator {
public:
	Calculator();
	~Calculator();

	float Parser9000(const std::string &expression);
};

