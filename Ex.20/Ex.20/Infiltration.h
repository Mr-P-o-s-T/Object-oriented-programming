#pragma once
#include "IAttackStrategy.h"
class Infiltration : public IAttackStrategy {
public:
	Infiltration() {}
	~Infiltration() {}

	const char *getStrategy() {
		return "";
	}
};
