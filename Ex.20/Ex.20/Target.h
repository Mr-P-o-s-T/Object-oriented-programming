#pragma once
enum class targetType {
	None,
	Field,
	Crossroad,
	Forest,
	Camp,
	Town,
	City,
	DOT,
	Bunker
};

enum class targetDefend {
	None,
	Militia,
	Recruits,
	TrainedTroops,
	UnderstaffedTroops,
	RegularTroops,
	EliteTroops
};

class Target {
public:
	targetType type;
	targetDefend garrison;

	Target() {}
	Target(targetType type, targetDefend garrison) {
		this->type = type; this->garrison = garrison;
	}
	~Target() {}
};
