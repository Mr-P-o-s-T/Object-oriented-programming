#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Ex.20\Commander.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ex20_Unittests {		
	TEST_CLASS(StrategyTests) {
	public:
		
		TEST_METHOD(AssaultStrategyCorrection) {
			IAttackStrategy *exmpl = new Assault();
			Assert::AreEqual(exmpl->getSpeech(), "That is a risky operation but capturing of this facility will bring an ending of this war...\n");
		}

		TEST_METHOD(AttritionStrategyCorrection) {
			IAttackStrategy *exmpl = new AttritionBattle();
			Assert::AreEqual(exmpl->getSpeech(), "Our enemy has been set down in deaf defence. This will be another attrition battle, but we have no choise. Remember: only wargoal is important now...\n");
		}

		TEST_METHOD(DominationStrategyCorrection) {
			IAttackStrategy *exmpl = new Domination();
			Assert::AreEqual(exmpl->getSpeech(), "Our forces in this region are more numberous and better trained. So show our might to our foes...\n");
		}

		TEST_METHOD(ExterminationStrategyCorrection) {
			IAttackStrategy *exmpl = new Extermination();
			Assert::AreEqual(exmpl->getSpeech(), "You will meet dangerous and well equiped enemy. So capture this position and show them no mercy...\n");
		}

		TEST_METHOD(InfilltrationStrategyCorrection) {
			IAttackStrategy *exmpl = new Infiltration();
			Assert::AreEqual(exmpl->getSpeech(), "Move quiet and capture that point...\n");
		}

		TEST_METHOD(SabotageStrategyCorrection) {
			IAttackStrategy *exmpl = new Sabotage();
			Assert::AreEqual(exmpl->getSpeech(), "Our enemies has a lots of equipment there, and has no suitable defence, so your goal is get them as most damage, as you can... But be careful: reinforcements are still probable... and dangerous...\n");
		}

		TEST_METHOD(StrategicStrikeStrategyCorrection) {
			IAttackStrategy *exmpl = new StrategicWeaponsStrike();
			Assert::AreEqual(exmpl->getSpeech(), "There is no way to capture this position by our men, so we will use our nukes. I know, most of you think about this cruel weanonary, but they will help us to finish this war...\n");
		}

	};
}