#pragma once
#include "include.h"
class TextureList
{
public:
	HRESULT Load(const char * filename,LPDIRECT3DTEXTURE9 * tex);
	TextureList(void);
	~TextureList(void);
};

