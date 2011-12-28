#include "stdafx.h"
#include "Scan.h"

#include "src/fsd/XeXtractor.h"
#include "src/fsd/SPA.h"

#include "Video.h"
#include "utils.h"

#include "include\kernel.h"
#include "Mount.h"

#include <queue>
#include <string>

#include <xmcore.h>

XLockFreeQueue <string> XexQueue;
XLockFreeQueue <string> DirQueue;
XLockFreeQueue <Game> RessourceQueue;

static DWORD crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

static DWORD crc32(DWORD crc, const void *buf, size_t size)
{
	const BYTE *p;

	p = (BYTE*)buf;
	crc = crc ^ ~0U;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return crc ^ ~0U;
}


//only check the filename
static HRESULT FastCheckXex(const char * filename){
	char drive[_MAX_DRIVE];
	char dir[_MAX_PATH];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	if(_splitpath_s(filename,drive,sizeof(drive),dir,sizeof(dir),fname,sizeof(fname),ext, sizeof(ext)) == 0)
	{
		if((stricmp(".xex",ext)==0) && (stricmp("default",fname)==0)){
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT CheckXex(const char * filename){
	char drive[_MAX_DRIVE];
	char dir[_MAX_PATH];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	if(_splitpath_s(filename,drive,sizeof(drive),dir,sizeof(dir),fname,sizeof(fname),ext, sizeof(ext)) == 0)
	{
		// Check Extention
		if(stricmp(".xex",ext)==0){
			printf("* Found xex - %s\r\n",filename);

			//XeXtractor & xtractor = XeXtractor::getInstance();
			XeXtractor xtractor;
			SPA spa;
			std::string tname;
			
			// Get title name from xex
			if(SUCCEEDED(xtractor.OpenXex(filename))){

				PBYTE pRessource=NULL;
				DWORD Size;
				
				HRESULT hr = xtractor.ExtractTitleSPA(&pRessource,&Size);
				if(hr==S_OK)
				{
					printf("Open spa for %s %x\r\n",filename,hr);
					
					if(pRessource){
						if(spa.OpenSPA(pRessource,Size)==S_OK){
							spa.GetTitleName(&tname,XGetLanguage());
							printf("=>%s\r\n",tname.c_str());
						}
						spa.CloseSPA();
					}
					
				}
				
			}
			
			
			// set filename by defaut
			if(tname.length()==0){
				tname = fname;
			}

			// compute nxeart path
			char nxeart[MAX_PATH];
			strcpy_s(nxeart,MAX_PATH,dir);
			strcat_s(nxeart,MAX_PATH,"nxeart");

			// Add game
			Game * current = new Game;
			ZeroMemory(current,sizeof(Game));
			// try to get
			xtractor.GetExecutionId(&current->XEX);
			current->name = tname;
			current->path = filename;
			current->type = G_XEX;
			current->texture_filename = nxeart;
			
			RessourceQueue.Add(current);

			xtractor.CloseXex();
			return S_OK;
		}
	}

	return E_FAIL;
}


static HRESULT _ScanFolder(const char * folder){
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	char found_file_name[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;

	// Check for $ in folder
	if(strstr(folder,"$")){
		return E_FAIL;
	}

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.

	length_of_arg = strlen(folder);

	if (length_of_arg > (MAX_PATH - 3))
	{
		printf(TEXT("\nDirectory path is too long.\n"));
		return E_FAIL;
	}

	printf(TEXT("\nListing directory is %s\n\n"), folder);

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.
	strcpy_s(szDir,MAX_PATH,folder);
	strcat_s(szDir,MAX_PATH,"\\*");

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) 
	{
		return dwError;
	} 

	// List all the files in the directory with some info about them.
	do
	{
		strcpy_s(found_file_name,MAX_PATH,folder);
		strcat_s(found_file_name,MAX_PATH,"\\");
		strcat_s(found_file_name,MAX_PATH,ffd.cFileName);

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_ScanFolder(found_file_name);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;

			if(FastCheckXex(found_file_name)==S_OK){
				string * q = new string;
				q->assign(found_file_name);
				XexQueue.Add(q);
			}
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{
	}

	FindClose(hFind);
	return dwError;
}



HRESULT  AddFolderToScan(char const  * dir){
	static int init = 0;
	if(init==0){ 
		init = 1;
		DirQueue.Initialize();
		XexQueue.Initialize();
		RessourceQueue.Initialize();
	}
	string * q = new string;
	q->assign(dir);
	DirQueue.Add(q);
	return S_OK;
}


static HANDLE ScanThread = NULL;
static HANDLE XexThread = NULL;
static HANDLE RessourceThread = NULL;

static DWORD WINAPI ScanFolderThread(LPVOID args){
	while(!DirQueue.IsEmpty()){
		string * q = DirQueue.Remove();
		_ScanFolder(q->c_str());
		delete (q);
	}
	return 0;
}

static DWORD WINAPI ScanXexThread(LPVOID args ){
	// always run when scan thread is running
	DWORD exitcode;
	
	do{
		GetExitCodeThread(ScanThread,&exitcode);

		while(!XexQueue.IsEmpty()){
			string * q = XexQueue.Remove();
			if(SUCCEEDED(CheckXex(q->c_str()))){

			}
			delete (q);
		}
	}
	while(exitcode==STILL_ACTIVE);
	return 0;
}

static DWORD WINAPI ScanRessourceThread(LPVOID args){
	// always run when xex thread is running
	DWORD exitcode;

	do{
		GetExitCodeThread(XexThread,&exitcode);

		while(!RessourceQueue.IsEmpty()){
			Game * q = RessourceQueue.Remove();
			
			// compute crc32 for cache filename
			char ftmp[256]; // tmp filename
			char buf[256]; // tmp crc32
			sprintf(buf, "%s%s%x", q->name.c_str(),q->path.c_str()),q->name.length();
			int size = strlen(buf);
			sprintf(ftmp,"game:\\cache\\%08x.dds",crc32(0xFFFFFFFF,&buf,size));

			string nxeart  = q->texture_filename;
			q->texture_filename = ftmp;

			q->texture = NULL;

			// check from cache
			if(FileExists(ftmp)){
				printf("Load From cache\r\n");
				q->texture = Video::LoadTextureFromFile(ftmp);
			}
			else
			// check from nxeart
			if(FileExists(nxeart)){
				printf("try loading from nxeart ... ");
				if(XContentMount("con",nxeart.c_str())==0){
					printf("loading from nxeart\r\n");
					// Load the texture and save it as dds in cache folder
					q->texture = Video::LoadTextureFromFile("con:\\nxebg.jpg");
					// save to dds for next scan
					Video::SaveTextureDDS(q->texture,ftmp);
					XContentUnMount("con");
				}
				else{
					printf("failed\r\n");
				}
			}
			else{
				printf("No texture ...\r\n");
				// default texture ...
				q->texture = Video::LoadTextureFromFile("game:\\cache\\noscreen.jpg");
				
			}

			q->name_texture = NULL;

			//g_GameList.AddGame(tname,filename,nxeart,G_XEX);
			g_GameList.AddGame(q[0]);

			

			delete (q);
		}
	}
	while(exitcode==STILL_ACTIVE);
	return 0;
}


HRESULT ScanFolder(){
	ScanThread = CreateThread(NULL,0,ScanFolderThread,NULL,CREATE_SUSPENDED  ,NULL);
	XexThread = CreateThread(NULL,0,ScanXexThread,NULL,CREATE_SUSPENDED  ,NULL);
	RessourceThread = CreateThread(NULL,0,ScanRessourceThread,NULL,CREATE_SUSPENDED  ,NULL);
	XSetThreadProcessor(ScanThread,3);
	ResumeThread(ScanThread);
	XSetThreadProcessor(XexThread,4);
	ResumeThread(XexThread);
	XSetThreadProcessor(RessourceThread,5);
	ResumeThread(RessourceThread);
	
	//WaitForSingleObject(RessourceThread,INFINITE);

	return S_OK;
}