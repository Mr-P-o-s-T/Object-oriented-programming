#pragma once
#include <vector>
#include <thread>

class Bucket {
public:


	Bucket() = default;
	Bucket(std::vector<int> &values) {
		swap(values, data);
	}
	~Bucket() = default;

	void AddData(int &newData) {
		data.push_back(newData);
	}

	std::vector<int> &GiveData() {
		return data;
	}

	void setNewThread(std::thread *newThread) {
		currThread = newThread;
		isFilled = true;
	}

	void finalizeCurrThread() {
		currThread->join();
		delete currThread;
	}

	bool isCurrThread(std::thread::id thr_id) {
		while (!isFilled) {
			std::this_thread::yield();
		}
		return thr_id == currThread->get_id();
	}
private:
	std::vector<int> data;
	std::thread *currThread = nullptr;
	bool isFilled = false;
};
