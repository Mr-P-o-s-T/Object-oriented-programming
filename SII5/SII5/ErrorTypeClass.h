#pragma once

enum ErrorType {
	NoError,
	NotEnoughMemory,
	Overflow,
	Underflow,
	UnknownError,
	AnotherError
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
	const char *stdMessages[AnotherError] = {"No any error detected...", "Not enough memory...", "Stack overflow...", "Stack is empty...", "Unknown error detected..."};
	const char *customMessage;
};
