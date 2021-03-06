#pragma once

enum ErrorType {
	NoError, 
	NotEnoughMemory, // bad alloc reinterpretation
	Overflow, // current depth == maxDepth
	Underflow, // current depth == 0
	Useless, // maxDepth == 0
	UnknownError,
	AnotherError // user`s custom error
};

class ErrorTypeClass {
public:
	ErrorTypeClass(const char *customMessage);
	ErrorTypeClass(ErrorType errorType, const char *customMessage = nullptr);
	~ErrorTypeClass();
	void ErrorDescription() const;
	ErrorType getErrorID() const {
		return errorID;
	 } 
private:
	ErrorType errorID;
	const char *stdMessages[AnotherError] = {"No any error detected...", "Not enough memory...", "Stack overflow...", "Stack is empty...", "This kind of stack is useless:", "Unknown error detected..."};
	const char *customMessage;
};
