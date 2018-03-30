#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SII5/Stack.cpp"
#include "../SII5/ErrorTypeClass.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTesting {		
	TEST_CLASS(PushingUnitTests) {
	public:
		TEST_METHOD(UselessStack) {
			// If stack`s depth is 0...
			try {
				// Assert::ExpectException() does not work... So this construction has been created...
				Stack<int> st(0);
				throw "e";
			}
			catch (const ErrorTypeClass&err) {
				Assert::AreEqual<size_t>(Useless, err.getErrorID());
			}
		}

		TEST_METHOD(PushingToEmptyStack) {
			Stack<int> st(1);

			// After creation stack must be empty...
			Assert::AreEqual<bool>(true, st.isEmpty());

			// ... and must not, after adding an element
			st.Push(1);
			Assert::AreEqual<bool>(false, st.isEmpty());
		}

		TEST_METHOD(PushingToNonEmptyStack) {
			Stack<int> st(2);

			st.Push(1);

			// After adding an element, head must point on new element
			st.Push(2);
			Assert::AreEqual<int>(2, st.Peek());
		}

		TEST_METHOD(PushingToFilledStack) {
			Stack<int> st(1);

			// Attempt of adding to filled stack must cause an excepion
			st.Push(1);
			try {
				st.Push(2);
				throw "e";
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Overflow, err.getErrorID());
			}
		}
	};

	TEST_CLASS(PeekingUnitTests) {
	public:
		TEST_METHOD(PeekingFromEmptyStack) {
			Stack<int> st(1);

			try {
				st.Peek();
				throw "e";
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Underflow, err.getErrorID());
			}
		}

		TEST_METHOD(PeekingFromNonEmptyStack) {
			Stack<int> st(1);
			st.Push(1);

			Assert::AreEqual<int>(1, st.Peek());
		}
	};

	TEST_CLASS(PopingUnitTests) {
	public:
		TEST_METHOD(PopingFromEmptyStack) {
			Stack<int> st(1);

			try {
				st.Pop();
				throw "e";
			}
			catch (const ErrorTypeClass &err) {
				Assert::AreEqual<size_t>(Underflow, err.getErrorID());
			}
		}

		TEST_METHOD(PopingFromNonEmptyStack) {
			Stack<int> st(3);

			st.Push(1);
			st.Push(2);

			st.Pop();

			Assert::AreEqual<int>(1, st.Peek());
		}
	};
}