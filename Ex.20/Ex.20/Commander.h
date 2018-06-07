#pragma once
#include "Target.h"
#include "AttackStrategies.h"
#include <string>
class Commander {
public:
	Commander() {}
	~Commander() {}

	void setTarget(Target newTarget) {
		currTarget = newTarget;
	}

	std::string getCurrStrategy() {
		switch (currTarget.type) {
		case targetType::None:
			strategy = new Domination();
			break;
		case targetType::Field:
			if (currTarget.garrison < targetDefend::EliteTroops) strategy = new Domination();
			else strategy = new AttritionBattle();
			break;
		case targetType::Forest:
			if (currTarget.garrison < targetDefend::UnderstaffedTroops) strategy = new Infiltration();
			else strategy = new Extermination();
			break;
		case targetType::Camp:
			if (currTarget.garrison < targetDefend::TrainedTroops) strategy = new Sabotage();
			else strategy = new Assault();
			break;
		case targetType::Town:
			if (currTarget.garrison < targetDefend::TrainedTroops) strategy = new Assault();
			else strategy = new AttritionBattle();
			break;
		case targetType::City:
			if (currTarget.garrison < targetDefend::Recruits) strategy = new Domination();
			else if (currTarget.garrison < targetDefend::EliteTroops) strategy = new AttritionBattle();
			else strategy = new StrategicWeaponsStrike();
			break;
		case targetType::DOT:
			if (currTarget.garrison < targetDefend::Recruits) strategy = new Assault();
			else strategy = new Extermination();
			break;
		case targetType::Bunker:
			if (currTarget.garrison < targetDefend::Recruits) strategy = new Assault();
			else strategy = new StrategicWeaponsStrike();
			break;
		}
		return strategy->getStrategy();
	}
private:
	Target currTarget;
	IAttackStrategy *strategy;
};
