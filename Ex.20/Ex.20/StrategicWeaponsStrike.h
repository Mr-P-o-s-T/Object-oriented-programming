#pragma once
#include "IAttackStrategy.h"
class StrategicWeaponsStrike : public IAttackStrategy {
public:
	StrategicWeaponsStrike() {}
	~StrategicWeaponsStrike() {}

	const char *getStrategy() {
		return "";
	}
};
