#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SII5/Stack.cpp"
#include "../SII5/ErrorTypeClass.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTesting {		
	TEST_CLASS(PushingUnitTests) {
	public:
		TEST_METHOD(PushingToEmptyStack) {
			Stack<int, 1> st;
			Assert::AreEqual<bool>(true, st.isEmpty());

			st.Push(1);
			Assert::AreEqual<bool>(false, st.isEmpty());
		}

		TEST_METHOD(PushingToNonEmptyStack) {
			Stack<int, 1> st;

			st.Push(1);

			st.Push(2);
			Assert::AreEqual<int>(2, st.Peek());
		}

		TEST_METHOD(PushingToFilledStack) {
			Stack<int, 1> st;

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
			Stack<int, 1> st;

			try {
				st.Peek();
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Underflow, err.getErrorID());
			}
		}

		TEST_METHOD(PeekingFromNonEmptyStack) {
			Stack<int, 1> st;
			st.Push(1);

			Assert::AreEqual<int>(1, st.Peek());
		}
	};

	TEST_CLASS(PopingUnitTests) {
	public:
		TEST_METHOD(PopingFromEmptyStack) {
			Stack<int, 1> st;

			try {
				st.Pop();
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Underflow, err.getErrorID());
			}
			
		}

		TEST_METHOD(PopingFromNonEmptyStack) {
			Stack<int, 3> st;

			st.Push(1);
			st.Push(2);

			st.Pop();

			Assert::AreEqual<int>(1, st.Peek());
		}
	};
}