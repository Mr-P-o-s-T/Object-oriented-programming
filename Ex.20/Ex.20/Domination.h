#pragma once
#include "IAttackStrategy.h"
class Domination : public IAttackStrategy {
public:
	Domination() {}
	~Domination() {}

	const char *getSpeech() {
		return "Our forces in this region are more numberous and better trained. So show our might to our foes...\n";
	}
};
