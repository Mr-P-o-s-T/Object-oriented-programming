#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Ex.11/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ex11UnitTests {		
	TEST_CLASS(ValueTests) {
	public:
		
		TEST_METHOD(ValueTest) {
			ITerm = new Value();
		}

	};
}