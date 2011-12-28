#pragma once
#include "include.h"

class HardwareManager
{
public:
	static BOOL FileExist(const char * filename);
	static unsigned int GetFileSize(const char * filename);

	static HRESULT SaveFile(const char * filename, void * pData, unsigned int size);
	static HRESULT LoadFile(const char * filename, void ** ppData, unsigned int * pSize);
	
	static HRESULT InitSystem();
	static HRESULT InitD3D();
	static HRESULT Cleanup();

	static void Update();

	static int GetWidth(){
		return 1280;
	}
	static int GetHeight(){
		return 720;
	}
};

