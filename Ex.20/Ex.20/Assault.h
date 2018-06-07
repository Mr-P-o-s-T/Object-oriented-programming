#pragma once
#include "IAttackStrategy.h"
class Assault :	public IAttackStrategy {
public:
	Assault() {}
	~Assault() {}

	const char *getStrategy() {
		return "sda";
	}
};
