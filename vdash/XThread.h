#pragma once
// implementation from http://www.mario-konrad.ch/index.php?page=30106
#include "stdafx.h"
#include <queue>
#include "XMutex.h"

typedef struct tagTHREADNAME_INFO
{
    DWORD dwType;     // must be 0x1000
    LPCSTR szName;    // pointer to name (in user address space)
    DWORD dwThreadID; // thread ID (-1 = caller thread)
    DWORD dwFlags;    // reserved for future use, must be zero
} THREADNAME_INFO;

static void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName )
{
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = szThreadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;

    __try
    {
        RaiseException( 0x406D1388, 0,
                    sizeof(info) / sizeof(DWORD),
		    (DWORD*)&info );
    }
    __except( EXCEPTION_CONTINUE_EXECUTION ) {
    }
}


class XThread
{
	public:
		HANDLE hthread;
		DWORD dwThreadId;
		static DWORD WINAPI dispatch(void * ptr){
			if (!ptr) 
				return 0;
			static_cast<XThread *>(ptr)->run();
			return 0;
		};
	protected:
		 virtual void run()=0;
	public:
		XThread(){
			hthread=NULL;
			dwThreadId=0;
		}
		virtual ~XThread(){
			if(hthread!=NULL)
			CloseHandle(hthread);	
		};
		void start(int HwThread, char * threadname){
			hthread = CreateThread(0,0,XThread::dispatch,this,CREATE_SUSPENDED,&dwThreadId);
			XSetThreadProcessor(hthread,HwThread);
			SetThreadName(dwThreadId,threadname);
			ResumeThread(hthread);
		};
		void join(){
			WaitForSingleObject(hthread,INFINITE);
		};
};