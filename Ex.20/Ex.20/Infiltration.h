#pragma once
#include "IAttackStrategy.h"
class Infiltration : public IAttackStrategy {
public:
	Infiltration() {}
	~Infiltration() {}

	const char *getSpeech() {
		return "Move quiet and capture that point...\n";
	}
};
