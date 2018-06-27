#pragma once
#include "IObserver.h"

template<class T>
class IObservable {
public:
	IObservable() {}
	virtual ~IObservable() {}

	virtual void addObserver(IObserver<T> &o) = 0;
	virtual void removeObserver(IObserver<T> &o) = 0;
	virtual void notify(T &data) = 0;
};
