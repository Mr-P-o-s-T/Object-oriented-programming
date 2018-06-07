#pragma once
#include "IAttackStrategy.h"
class Extermination : public IAttackStrategy {
public:
	Extermination() {}
	~Extermination() {}

	const char *getSpeech() {
		return "You will meet dangerous and well equiped enemy. So capture this position and show them no mercy...\n";
	}
};
