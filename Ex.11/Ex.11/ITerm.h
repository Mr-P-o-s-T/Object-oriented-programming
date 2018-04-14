#pragma once

class ITerm {
public:
	virtual ~ITerm() = 0;

	virtual void addSubterm(ITerm *t) = 0;
	virtual void deleteSubterm(size_t index) = 0;
	virtual void deleteSubterms(size_t indexFrom, size_t indexTo) = 0;
	virtual float getValue() = 0;
};
