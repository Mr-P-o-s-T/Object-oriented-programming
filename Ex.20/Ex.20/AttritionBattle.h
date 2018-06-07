#pragma once
#include "IAttackStrategy.h"
class AttritionBattle :	public IAttackStrategy {
public:
	AttritionBattle() {}
	~AttritionBattle() {}

	const char *getSpeech() {
		return "Our enemy has been set down in deaf defence. This will be another attrition battle, but we have no choise. Remember: only wargoal is important now...\n";
	}
};
