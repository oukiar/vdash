#pragma once
// implementation from http://www.mario-konrad.ch/index.php?page=30106
#include "stdafx.h"
#include <queue>
#include "XMutex.h"


template <class T> class XPool{
private:
	std::queue<T> data;
	XMutex mutex;
	size_t max_size;
	size_t spin_time;
public:
	XPool(size_t max_size = 10, size_t spin_time = 50): max_size(max_size), spin_time(spin_time){

	}

	~XPool(){
		mutex.lock();
		while (data.size()) data.pop();
		mutex.unlock();
	}

	size_t size(){
		mutex.lock();
		size_t size = data.size();
		mutex.unlock();
		return size;
	}

	void push(T item){
		mutex.lock();
		while(data.size()>=max_size){
			mutex.unlock();
			//Sleep(spin_time*1000);
			mutex.lock();
		}
		data.push(item);
		mutex.unlock();
	}

	T pop(){
		T item;
		mutex.lock();
		while(data.size()<=0){
			mutex.unlock();
			//Sleep(spin_time*1000);
			mutex.lock();
		}
		item = data.front();
		data.pop();
		mutex.unlock();
		return item;
	}
};


