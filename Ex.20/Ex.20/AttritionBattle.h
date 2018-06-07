#pragma once
#include "IAttackStrategy.h"
class AttritionBattle :	public IAttackStrategy {
public:
	AttritionBattle() {}
	~AttritionBattle() {}

	const char *getStrategy() {
		return "";
	}
};
