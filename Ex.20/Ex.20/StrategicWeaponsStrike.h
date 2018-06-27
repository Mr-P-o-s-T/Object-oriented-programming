#pragma once
#include "IAttackStrategy.h"
class StrategicWeaponsStrike : public IAttackStrategy {
public:
	StrategicWeaponsStrike() {}
	~StrategicWeaponsStrike() {}

	const char *getSpeech() {
		return "There is no way to capture this position by our men, so we will use our nukes. I know, most of you think about this cruel weanonary, but they will help us to finish this war...\n";
	}
};
