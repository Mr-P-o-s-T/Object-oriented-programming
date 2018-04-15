#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Ex.11/Calculator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ex11UnitTests {		
	TEST_CLASS(ValueTests) {
	public:
		
		TEST_METHOD(ValueTest) {
			ITerm *val = new Value(2.57f);
			if (abs(2.57f - val->GetValue()) > 0.01f) {
				delete val;
				Assert::Fail();
			}
			delete val;
		}

	};

	TEST_CLASS(OperationsTests) {
	public:

		TEST_METHOD(GettingValueWithoutAddingAllOperands) {
			ITerm *plus = new Plus;
			plus->addSubterm(new Value(1.0f));
			try {
				plus->GetValue();
			}
			catch (const std::exception&) {
				delete plus;
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(AddingMoreThanNOperands) {
			ITerm *uPlus = new UnarPlus;
			uPlus->addSubterm(new Value(2.2f));
			try {
				uPlus->addSubterm(new Value(2.3f));
			}
			catch (const std::exception&) {
				delete uPlus;
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(DeletingFromOperatorWithNoAddedSubterms) {
			ITerm *uPlus = new UnarPlus;
			try {
				uPlus->deleteSubterm(0);
			}
			catch (const std::exception&) {
				delete uPlus;
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(OutOfRangeDeleting) {
			ITerm *uPlus = new UnarPlus;
			uPlus->addSubterm(new Value(2.2f));
			try {
				uPlus->deleteSubterm(1);
			}
			catch (const std::exception&) {
				delete uPlus;
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(InRangeDeleting) {
			ITerm *uPlus = new UnarPlus;
			uPlus->addSubterm(new Value(2.2f));
			try {
				uPlus->deleteSubterm(0);
			}
			catch (const std::exception&) {
				delete uPlus;
				Assert::Fail();
			}
			delete uPlus;
		}

		TEST_METHOD(MultiplyedOutOfRangeDeleting) {
			ITerm *plus = new Plus;
			plus->addSubterm(new Value(2.2f));
			plus->addSubterm(new Value(2.2f));
			try {
				plus->deleteSubterms(0,3);
			}
			catch (const std::exception&) {
				delete plus;
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(MultiplyedInRangeDeleting) {
			ITerm *plus = new Plus;
			plus->addSubterm(new Value(1.0f));
			plus->addSubterm(new Value(1.0f));
			plus->deleteSubterms(0, 1);

			plus->addSubterm(new Value(1.0f));
			try {
				plus->addSubterm(new Value(1.0f));
			}
			catch (const std::exception&) {
				delete plus;
				Assert::Fail();
			}
			delete plus;
		}

		TEST_METHOD(UnarPlusValueTest) {
			ITerm *uPlus = new UnarPlus;
			uPlus->addSubterm(new Value(2.2f));
			if (abs(2.2f - uPlus->GetValue()) > 0.01f) {
				delete uPlus;
				Assert::Fail();
			}
			delete uPlus;
		}

		TEST_METHOD(UnarMinusValueTest) {
			ITerm *uMinus = new UnarMinus;
			uMinus->addSubterm(new Value(2.2f));
			if (abs(-2.2f - uMinus->GetValue()) > 0.01f) {
				delete uMinus;
				Assert::Fail();
			}
			delete uMinus;
		}

		TEST_METHOD(PlusValueTest) {
			ITerm *plus = new Plus;
			plus->addSubterm(new Value(2.2f));
			plus->addSubterm(new Value(2.3f));
			if (abs(4.5f - plus->GetValue()) > 0.01f) {
				delete plus;
				Assert::Fail();
			}
			delete plus;
		}

		TEST_METHOD(MinusValueTest) {
			ITerm *minus = new Minus;
			minus->addSubterm(new Value(2.2f));
			minus->addSubterm(new Value(2.3f));
			if (abs(-0.1f - minus->GetValue()) > 0.01f) {
				delete minus;
				Assert::Fail();
			}
			delete minus;
		}

		TEST_METHOD(MultiplyValueTest) {
			ITerm *multiply = new Multiply;
			multiply->addSubterm(new Value(2.2f));
			multiply->addSubterm(new Value(2.3f));
			if (abs(5.06f - multiply->GetValue()) > 0.01f) {
				delete multiply;
				Assert::Fail();
			}
			delete multiply;
		}

		TEST_METHOD(DivideValueTest) {
			ITerm *divide = new Divide;
			divide->addSubterm(new Value(2.3f));
			divide->addSubterm(new Value(4.6f));
			if (abs(0.5f - divide->GetValue()) > 0.01f) {
				delete divide;
				Assert::Fail();
			}
			delete divide;
		}

		TEST_METHOD(ExponentValueTest) {
			ITerm *exponent = new Exponent;
			exponent->addSubterm(new Value(2.0f));
			exponent->addSubterm(new Value(3.0f));
			if (abs(8.0f - exponent->GetValue()) > 0.01f) {
				delete exponent;
				Assert::Fail();
			}
			delete exponent;
		}

	};
}