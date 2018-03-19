#include "ErrorTypeClass.h"
#include <iostream>

ErrorTypeClass::ErrorTypeClass(const char *customMessage) {
	errorID = AnotherError;
	this->customMessage = customMessage;
}

ErrorTypeClass::ErrorTypeClass(ErrorType errorType, const char *customMessage) {
	errorID = errorType;
	this->customMessage = customMessage;
}

ErrorTypeClass::~ErrorTypeClass() {

}

void ErrorTypeClass::ErrorDescription() const {
	if (errorID == AnotherError) {
		std::cout << customMessage << "\n";
	}
	else {
		std::cout << stdMessages[errorID];
		if (customMessage) std::cout << " " << customMessage;
		std::cout << "\n";
	}
}
