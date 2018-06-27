#pragma once
#include "IAttackStrategy.h"
class Assault :	public IAttackStrategy {
public:
	Assault() {}
	~Assault() {}

	const char *getSpeech() {
		return "That is a risky operation but capturing of this facility will bring an ending of this war more closer...\n";
	}
};
