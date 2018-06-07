#pragma once
#include "IAttackStrategy.h"
class Domination : public IAttackStrategy {
public:
	Domination() {}
	~Domination() {}

	const char *getStrategy() {
		return "";
	}
};
