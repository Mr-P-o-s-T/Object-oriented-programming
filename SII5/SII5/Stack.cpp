#include "Stack.h"

void Stack::Push(int data) {
	try	{
		if (depth == maxDepth) throw ErrorTypeClass(Overflow, "Adding not alloved...");
		top = new Item(data, top);
		depth++;
	}
	catch (const std::bad_alloc &) {
		throw ErrorTypeClass(NotEnoughMemory);
	}
	catch (const ErrorTypeClass &) {
		throw;
	}
	catch (...) {
		if (!isEmpty()) delete top;
		throw ErrorTypeClass(UnknownError, "Stack`s clearing up...");
	}
}

int Stack::Pop() {
	try {
		if (isEmpty()) throw ErrorTypeClass(Underflow, "Deleting not allowed...");
		Item *tmp = top;
		top = top->prevTop;
		int result = tmp->data;
		tmp->prevTop = nullptr;
		delete tmp;
		depth--;
		return result;
	}
	catch (const ErrorTypeClass &) {
		throw;
	}
	catch (...) {
		if (!isEmpty()) delete top;
		throw ErrorTypeClass(UnknownError, "Stack`s clearing up...");
	}
}
