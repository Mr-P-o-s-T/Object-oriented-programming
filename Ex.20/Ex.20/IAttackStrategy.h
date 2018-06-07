#pragma once
class IAttackStrategy {
public:
	IAttackStrategy() {}
	virtual ~IAttackStrategy() {}

	virtual const  char*getStrategy() = 0;
};
