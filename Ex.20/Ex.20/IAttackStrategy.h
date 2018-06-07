#pragma once
class IAttackStrategy {
public:
	IAttackStrategy() {}
	virtual ~IAttackStrategy() {}

	virtual const  char *getSpeech() = 0;
};
