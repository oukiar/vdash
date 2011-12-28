#pragma once

#include <string>

static inline int FileExists(const char * filename)
{
	int ret = GetFileAttributes(filename) != 0xFFFFFFFF;
	/*
	FILE * fd = fopen(filename,"rb");
	int ret = (fd!=NULL);
	if(fd)
		fclose(fd);

	if(!ret){
		printf("File %s not found - %08x\r\n",filename,GetFileAttributes(filename));
	}
	*/
	return ret;
}

static inline int FileExists(std::string filename)
{
	return FileExists(filename.c_str());
}

static inline char* wchartochar(const WCHAR* str,int mLength)
{
	int Length = WideCharToMultiByte(CP_UTF8,0,str,mLength,NULL,0,NULL,NULL);	
	char* retVal = new char[Length+1];
	WideCharToMultiByte(CP_UTF8,0,str,mLength,retVal,Length,NULL,NULL);
	return retVal;
}




