// main file
#include "Commander.h"
#include <iostream>
using namespace std;

int main() {
	Commander commander;
	Target targets[8] = { Target(targetType::Crossroad, targetDefend::UnderstaffedTroops), Target(targetType::Forest, targetDefend::RegularTroops), 
		Target(targetType::Town, targetDefend::Recruits), Target(targetType::Camp, targetDefend::EliteTroops), Target(targetType::Bunker, targetDefend::TrainedTroops), 
		Target(targetType::City, targetDefend::UnderstaffedTroops), Target(targetType::DOT, targetDefend::Militia), Target(targetType::Forest, targetDefend::Recruits) };
	int item;
	cout << "Recon`s report:\n1. On crossroad is situated temprorary base of recently retreated division...\n2. In forest, there are some fresh enemy troops in ambush...\n"\
		"3. A little town near bridge is defended by couple brigades of recruits...\n4. A camp of division is on our forces way...\n5. The bunker of our foe`s first line of defence."\
		 "And there are a lot of enemy`s troops that are ready to kill our men...\n6. Industrial centre of our enemy. Defended by retreated division...\n7. A DOT defended by armed civils...\n"\
		"8. A group of enemy`s recruits is hiding in nearest forest...\n\n";
	cin >> item;
	commander.setTarget(targets[--item]);
	cout << "Few hours later...\nCommander is online and ready to give orders:\n" << commander.getSpeech();
	system("pause");
	return 0;
}