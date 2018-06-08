#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Ex.22/Observer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ex22_Unittests {		
	TEST_CLASS(ObserverUnitTests) {
	public:

		TEST_METHOD(HistoryListUnitTest) {
			ObservableDouble a;
			HistoryList list;
			a.addObserver(list);
			a.setValue(2.0);
			a.setValue(3.0);
			a.setValue(1.0);
			std::vector<double> result = list.getHistory(), answer({ 2.0, 3.0, 1.0 });
			for (size_t i = 0; i < result.size(); i++) 
				if (abs(result[i] - answer[i]) >= 0.01) Assert::Fail();			
		}

		TEST_METHOD(MeanUnitTest) {
			ObservableDouble a;
			Mean mean;
			a.addObserver(mean);
			a.setValue(1.0);
			a.setValue(2.0);
			a.setValue(3.0);
			if (abs(mean.getMean() - 2.0) >= 0.01) Assert::Fail();
		}
		
		TEST_METHOD(SummatorUnitTest) {
			ObservableDouble a;
			Summator summ;
			a.addObserver(summ);
			a.setValue(1.0);
			a.setValue(2.0);
			a.setValue(3.0);
			if (abs(summ.getSumm() - 6.0) >= 0.01) Assert::Fail();
		}

		TEST_METHOD(SorterUnitTest) {
			ObservableDouble a;
			Sorter list;
			a.addObserver(list);
			a.setValue(2.0);
			a.setValue(3.0);
			a.setValue(1.0);
			std::vector<double> result = list.getSortedValues(), answer({ 1.0, 2.0, 3.0 });
			for (size_t i = 0; i < result.size(); i++)
				if (abs(result[i] - answer[i]) >= 0.01) Assert::Fail();
		}

	};
}