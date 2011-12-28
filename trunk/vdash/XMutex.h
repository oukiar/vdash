#pragma once
#include <xtl.h>
class XMutex
{
private:
	CRITICAL_SECTION mCs;
public:
	XMutex(void){
		InitializeCriticalSection(&mCs);
	}
	~XMutex(void){
		DeleteCriticalSection(&mCs);
	}

	void lock(){
		EnterCriticalSection(&mCs);
	}

	void unlock(){
		LeaveCriticalSection(&mCs);
	}

	void trylock(){
		TryEnterCriticalSection(&mCs);
	}
};

