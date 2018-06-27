#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LAB.8 (Single threaded)/BucketSorter.cpp"
#include "../LAB.8 (Single threaded)/CombSorter.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SingleThreadedSorterTests {		
	TEST_CLASS(CombSorterTests) {
	public:
		TEST_METHOD(PositiveArraySorting) {
			std::vector<int> arrExample({ 8, 3 , 7 , 8 , 10, 15, 3, 1, 0 }), sortedExample({ 0, 1, 3, 3, 7, 8, 8, 10, 15 });
			Bucket bckt(arrExample);
			CombSorter srtr;
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(CommonArraySorting) {
			std::vector<int> arrExample({ 8, -3 , 7 , -8 , 10, -15, 3, -1, 0 }), sortedExample({ -15, -8, -3, -1, 0, 3, 7, 8, 10 });
			Bucket bckt(arrExample);
			CombSorter srtr;
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(OneElementArraySorting) {
			std::vector<int> arrExample({ 8 }), sortedExample({ 8 });
			Bucket bckt(arrExample);
			CombSorter srtr;
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(EmptyArraySorting) {
			std::vector<int> arrExample({ });
			Bucket bckt(arrExample);
			CombSorter srtr;
			srtr.Sort(bckt);
		}
	};

	TEST_CLASS(BucketSorterTests) {
	public:
		TEST_METHOD(PositiveArraySorting) {
			std::vector<int> arrExample({ 8, 3 , 7 , 8 , 10, 15, 3, 1, 0 }), sortedExample({ 0, 1, 3, 3, 7, 8, 8, 10, 15 });
			Bucket bckt(arrExample);
			BucketSorter srtr(2);
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(CommonArraySorting) {
			std::vector<int> arrExample({ 8, -3 , 7 , -8 , 10, -15, 3, -1, 0 }), sortedExample({ -15, -8, -3, -1, 0, 3, 7, 8, 10 });
			Bucket bckt(arrExample);
			BucketSorter srtr(2);
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(OneElementArraySorting) {
			std::vector<int> arrExample({ 8 }), sortedExample({ 8 });
			Bucket bckt(arrExample);
			BucketSorter srtr(2);
			srtr.Sort(bckt);
			std::vector<int> res = bckt.GiveData();
			for (size_t i = 0; i < res.size(); i++) {
				if (sortedExample[i] != res[i]) Assert::Fail();
			}
		}

		TEST_METHOD(EmptyArraySorting) {
			std::vector<int> arrExample({ });
			Bucket bckt(arrExample);
			BucketSorter srtr(2);
			srtr.Sort(bckt);
		}
	};
}
