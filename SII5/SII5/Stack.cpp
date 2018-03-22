#include "Stack.h"

template <class T, size_t maxDepth>
void Stack <T, maxDepth>::Push(T data) {
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

template <class T, size_t maxDepth>
T Stack <T, maxDepth>::Pop() {
	try {
		if (isEmpty()) throw ErrorTypeClass(Underflow, "Deleting not allowed...");
		Item *tmp = top;
		top = top->prevTop;
		T result = tmp->data;
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
