#pragma once
#include "IAttackStrategy.h"
class Sabotage : public IAttackStrategy {
public:
	Sabotage() {}
	~Sabotage() {}

	const char *getSpeech() {
		return "Our enemies has a lots of equipment there, and has no suitable defence, so your goal is get them as most damage, as you can... But be careful: reinforcements are still probable... and dangerous...\n";
	}
};
