#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Ex.11/Calculator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ex11UnitTests {		
	TEST_CLASS(ValueTests) {
	public:
		
		TEST_METHOD(ValueTest) {
			// Value`s GetValue() must return current value of this Value

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
			// If not all operands are set, GetValue must throw an exception

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
			// If all operands are set, addSubterm() must throw an exception

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
			// If not all operands are set, deleteSubterm() must throw an exception

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
			// If you want, for example, delete an fourth operand of binary operator, deleteSubterm() must throw an exception

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
			// If you want, for example, delete an first operpand of binary operator, throwed exception is an error

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
			// If you want, for example, delete from second to fourth operands of binary operator (or from third to fourth operator), deleteSubterm() must throw an exception

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
			// If you want, for example, delete from first to second operpands of ternary operator (or even all operatnds), throwed exception is an error

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
			// Unar plus must return a value of it`s operand

			ITerm *uPlus = new UnarPlus;
			uPlus->addSubterm(new Value(2.2f));
			if (abs(2.2f - uPlus->GetValue()) > 0.01f) {
				delete uPlus;
				Assert::Fail();
			}
			delete uPlus;
		}

		TEST_METHOD(UnarMinusValueTest) {
			// Unar minus must return a negative value of it`s operand

			ITerm *uMinus = new UnarMinus;
			uMinus->addSubterm(new Value(2.2f));
			if (abs(-2.2f - uMinus->GetValue()) > 0.01f) {
				delete uMinus;
				Assert::Fail();
			}
			delete uMinus;
		}

		TEST_METHOD(PlusValueTest) {
			// Plus must return a sum of values of it`s operands
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
			// Minus must return a difference of values of it`s operands

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
			// Multiply must return a composition of values of it`s operands

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
			// Divide must return a ratio of values of it`s operands

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
			// Exponent must return a potentiation of values of it`s operands

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

	TEST_CLASS(CalculatorUnitTests) {
	public:

		TEST_METHOD(EmptyExpression) {
			// Empty string must cause an exception

			Calculator calc;

			try {
				calc.Parser9000("");
			}
			catch (const std::exception&) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(UnsupportedSymbol) {
			// Unsupported symbol in string must cause an exception

			Calculator calc;

			try {
				calc.Parser9000("2+3*x");
			}
			catch (const std::exception&) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(NoOpenBracket) {
			// Close bracket without open one in string must cause an exception

			Calculator calc;

			try {
				calc.Parser9000("2+3*4)");
			}
			catch (const std::exception&) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(NoCloseBracket) {
			// Open bracket without close one in string must cause an exception

			Calculator calc;

			try {
				calc.Parser9000("(2+3*4");
			}
			catch (const std::exception&) {
				return;
			}
			Assert::Fail();
		}

		TEST_METHOD(WholeNumbersTest) {
			Calculator calc;

			Assert::AreEqual(calc.Parser9000("-1+2-3*4/5^6"), 0.999232f, 0.0000001f);
		}

		TEST_METHOD(FloatNumbersTest) {
			Calculator calc;

			Assert::AreEqual(calc.Parser9000("36.5/4.37*12+6589"), 6689.228833f, 0.0000001f);
		}

	};
}