#pragma once
#include "IAttackStrategy.h"
class Sabotage : public IAttackStrategy {
public:
	Sabotage() {}
	~Sabotage() {}

	const char *getStrategy() {
		return "";
	}
};
