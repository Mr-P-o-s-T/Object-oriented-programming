#pragma once

class ITerm {
public:
	ITerm();

	virtual float getValue() = 0;

	virtual ~ITerm();
};
