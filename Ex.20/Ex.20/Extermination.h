#pragma once
#include "IAttackStrategy.h"
class Extermination : public IAttackStrategy {
public:
	Extermination() {}
	~Extermination() {}

	const char *getStrategy() {
		return "";
	}
};
