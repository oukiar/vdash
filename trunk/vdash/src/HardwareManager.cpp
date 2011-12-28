#include "StdAfx.h"
#include "HardwareManager.h"

BOOL HardwareManager::FileExist(const char * filename){
	HANDLE hFile = CreateFileA( 
		filename, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, 0, NULL
	);

	// File not found
	if( hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	CloseHandle( hFile );
	return TRUE;
};

unsigned int HardwareManager::GetFileSize(const char * filename){
	// Open the file for reading
	HANDLE hFile = CreateFileA( 
		filename, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, 0, NULL 
	);

	if( hFile == INVALID_HANDLE_VALUE)
		return 0;

	unsigned int filesize = ::GetFileSize( hFile, NULL );

	CloseHandle( hFile );

	return filesize;
}

HRESULT HardwareManager::SaveFile(const char * filename, void * pData, unsigned int size){

	HANDLE hFile = CreateFileA( 
		filename, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, 0, NULL
	);

	// File not found
	if( hFile == INVALID_HANDLE_VALUE )
		return E_HANDLE;

	DWORD NumberOfBytesWritten;
	if(WriteFile( hFile, pData, size, &NumberOfBytesWritten, NULL ) == TRUE){
		// free handle
		CloseHandle( hFile );

		if( NumberOfBytesWritten != size ){
			// Write Failed ...
			return E_FAIL;
		}

		return S_OK;
	}

	// Error ...
	DebugBreak();
		
	return E_FAIL;
}

HRESULT HardwareManager::LoadFile(const char * filename, void ** ppData, unsigned int * pSize){

	if(ppData==NULL){
		// Error ...
		DebugBreak();
	}

	if( pSize )
		*pSize = 0;

	// Open the file for reading
	HANDLE hFile = CreateFileA( 
		filename, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, 0, NULL 
	);

	if( hFile == INVALID_HANDLE_VALUE)
		return E_HANDLE;

	DWORD dwFileSize = ::GetFileSize( hFile, NULL );
	VOID* pFileData = malloc( dwFileSize );

	if( NULL == pFileData )
	{
		CloseHandle( hFile );
		return E_OUTOFMEMORY;
	}

	DWORD dwBytesRead;
	if( !ReadFile( hFile, pFileData, dwFileSize, &dwBytesRead, NULL ) )
	{
		CloseHandle( hFile );
		free( pFileData );
		return E_FAIL;
	}

	// Finished reading file
	CloseHandle( hFile );

	if( dwBytesRead != dwFileSize )
	{
		free( pFileData );
		return E_FAIL;
	}

	if( pSize )
		*pSize = dwFileSize;
	*ppData = pFileData;

	return S_OK;
}