#pragma once

#include "kernel.h"
#include "types.h"
//#include "devio.h"
#include "exconfig.h"
//#include "xekey.h"

#ifdef _XBOX
#else
#include <windows.h>
#endif

extern "C"{

	typedef struct _CONSOLE_PUBLIC_KEY {
		BYTE PublicExponent[0x04];
		BYTE Modulus[0x80];
	} CONSOLE_PUBLIC_KEY, *PCONSOLE_PUBLIC_KEY;

	typedef struct _XE_CONSOLE_CERTIFICATE {
		WORD				  CertSize;
		BYTE				  ConsoleId[0x05];
		BYTE				  ConsolePartNumber[0x0B];
		BYTE				  Reserved[0x04];
		WORD				  Privileges;
		DWORD			  ConsoleType;
		BYTE				  ManufacturingDate[0x08];
		CONSOLE_PUBLIC_KEY ConsolePublicKey;
		BYTE				  Signature[0x100];
	} XE_CONSOLE_CERTIFICATE, *PXE_CONSOLE_CERTIFICATE;


	int XeKeysGetConsoleType(WORD* ConsoleType);

	// Profile Exports
	int XeKeysUnObfuscate(int ObfuscationKey, char* encryptedBuffer, int encryptedLength, char* outputBuffer, int* outputLength);
	int XeKeysObfuscate(int ObfuscationKey, char* decryptedBuffer, int decryptedLength, char* outputBuffer, int* outputLength);
	//DWORD XeKeysGetKey(DWORD keyNum, VOID* buffer, DWORD* bufferSize);
	BOOL XeKeysGetConsoleTypeCustom(DWORD* ConsoleType);

	// Compression
	typedef struct _LZX_DECOMPRESS {
		LONG WindowSize;
		LONG CpuType;
	} LZX_DECOMPRESS, *PLZX_DECOMPRESS;

	DWORD LDICreateDecompression(DWORD* pcbDataBlockMax, 
		LZX_DECOMPRESS* pvConfiguration,
		DWORD pfnma, DWORD pfnmf,
		VOID* pcbSrcBufferMin,
		DWORD* unknow, DWORD* pcbDecompressed);
	DWORD LDIDecompress(DWORD context, BYTE* pbSrc, WORD cbSrc,
		BYTE* pdDst, DWORD* pcbDecompressed);
	DWORD LDIDestroyDecompression(DWORD contect);
}