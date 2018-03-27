#pragma once
#include "ErrorTypeClass.h"
#include <exception>

template <class T>
class Stack {
public:
	// Creates empty stack
	Stack(size_t maxDepth) {
		depth = 0;
		this->maxDepth = maxDepth;
		top = nullptr;
		if (!maxDepth) throw ErrorTypeClass(Useless, "maximal depth is zero...");
	}

	// Copies
	Stack(const Stack &source) {
		try {
			top = source.top ? new Item(*source.top) : nullptr;
			depth = source.depth;
			maxDepth = source.maxDepth;
		}
		catch (const std::bad_alloc&) {
			throw ErrorTypeClass(NotEnoughMemory, "Copying not possible...");
		}
		catch (...) {
			if (!isEmpty()) delete top;
			throw ErrorTypeClass(UnknownError, "Stack`s clearing up...");
		}
	}

	// Moves
	Stack(Stack &&container) {
		top = container.top;
		depth = container.depth;
		maxDepth = container.maxDepth;
		container.top = nullptr;
	}

	// Clears up
	~Stack() {
		if (!isEmpty()) delete top;
	}

	// Default stack operation. Throws an exception when stack overflow, or can not allocate memory for a new item
	void Push(T data);

	// Default stack operation. Throws an exception when stack is empty
	T Pop();

	// Default stack operation. Throws an exception when stack is empty
	T & Peek() const {
		if (isEmpty()) throw ErrorTypeClass(Underflow, "Nothing to peek...");
		return top->data;
	}

	// Emptiness checking
	bool isEmpty() const {
		return !depth;
	}
private:
	class Item {
	public:
		Item(T data, Item *prev) {
			this->data = data;
			prevTop = prev;
		}
		Item(const Item &source) {
			prevTop = source.prevTop ? new Item(*source.prevTop) : nullptr;
			data = source.data;
		}
		~Item() {
			if (prevTop) delete prevTop;
		}
	private:
		T data;
		Item *prevTop;

		friend class Stack;
	} *top;

	size_t depth, maxDepth;
};
