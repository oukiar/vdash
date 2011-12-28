#include "stdafx.h"
#include "ImgConvert.h"

HRESULT ImgConvert(const char *srcFilename, const char * dstFilename, D3DXIMAGE_FILEFORMAT fmt){
#if 0
	LPDIRECT3DTEXTURE9 texture = NULL;


	HRESULT hr= D3DXCreateTextureFromFileExA( 
			g_pd3dDevice,
			srcFilename, 
			1280,
			720, 
			1,
			0, 
			D3DFMT_UNKNOWN, 
			D3DPOOL_DEFAULT , 
			D3DX_FILTER_BOX , 
			D3DX_FILTER_BOX , 
			0, 
			NULL, 
			NULL, 
			&texture
		);

	if(SUCCEEDED(hr)){
		return D3DXSaveTextureToFileA(dstFilename,fmt,texture,NULL);
	}
#endif
	return E_FAIL;
}