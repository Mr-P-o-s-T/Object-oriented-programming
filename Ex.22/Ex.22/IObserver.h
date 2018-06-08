#pragma once

template <class T>
class IObserver {
public:
	IObserver() {}
	virtual ~IObserver() {}

	virtual void updated(T &data) = 0;

	virtual const T &getResult() = 0;
};
