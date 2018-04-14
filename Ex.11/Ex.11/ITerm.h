#pragma once

class ITerm {
public:
	virtual ~ITerm() = 0;

	virtual void addSubterm(ITerm &t) = 0;
	virtual void deleteSubTerm(bool first) = 0;
	virtual float getValue() = 0;
};

ITerm::~ITerm() { }