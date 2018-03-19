#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SII5/Stack.cpp"
#include "../SII5/ErrorTypeClass.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTesting {		
	TEST_CLASS(PushingUnitTests) {
	public:
		
		TEST_METHOD(PushingToEmptyStack) {
			Stack st(1);
			Assert::AreEqual<bool>(true, st.isEmpty());

			st.Push(1);
			Assert::AreEqual<bool>(false, st.isEmpty());
		}

		TEST_METHOD(PushingToNonEmptyStack) {
			Stack st(3);

			st.Push(1);

			st.Push(2);
			Assert::AreEqual<int>(2, st.Peek());
		}

		TEST_METHOD(PushingToFilledStack) {
			Stack st(1);

			st.Push(1);
			try {
				st.Push(2);
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Overflow, err.getErrorID());
			}
		}

	};

	TEST_CLASS(PeekingUnitTests) {
	public:

		TEST_METHOD(PeekingFromEmptyStack) {
			Stack st(1);

			try {
				st.Peek();
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Underflow, err.getErrorID());
			}
		}

		TEST_METHOD(PeekingFromNonEmptyStack) {
			Stack st(1);
			st.Push(1);

			Assert::AreEqual<int>(1, st.Peek());
		}

	};
}