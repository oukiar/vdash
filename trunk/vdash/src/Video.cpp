#include "stdafx.h"
#include "Video.h"

#include "shaders.h"

#include "AtgApp.h"
#include "AtgFont.h"
#include "AtgUtil.h"


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
// Used to create the D3DDevice
LPDIRECT3D9             g_pD3D = NULL; 
// Our rendering device
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
// Buffer to hold MM
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; 

XMMATRIX matWVP, matView, matProj;
IDirect3DPixelShader9* g_pPixelShaderReflexion = NULL;
IDirect3DPixelShader9* g_pPixelShader = NULL;
IDirect3DVertexShader9* g_pVertexShader = NULL;
IDirect3DVertexDeclaration9* g_pVertexDecl = NULL;

static ATG::Font vFont;

int i_theme = 0;
Themes m_themes[5];
int cs;
static float fcs;
static float video_time = 0.f;

void clamp_cs(){
	if(cs>=g_GameList.Length())
	{
		cs=g_GameList.Length()-1;
	}
	if(cs<0){
		cs=0;
	}
}


Themes * Video::GetTheme(){
	return &m_themes[i_theme];
};

void Video::MoveLeft(){
	cs--;
	clamp_cs();
};
void Video::MoveRight(){
	cs++;
	clamp_cs();
};
void Video::MoveUp(){
	i_theme++;
	if(i_theme>4)
		i_theme=4;
};
void Video::MoveDown(){
	i_theme--;
	if(i_theme<0)
		i_theme=0;
};

void Video::InitDefaultThemes(){
	// Cover Flow
	m_themes[0].PosCenter.x = 0.f;
	m_themes[0].PosCenter.y = 0.8f;
	m_themes[0].PosCenter.z = 5.f;

	m_themes[0].PosCenter.rotX = 0.f;
	m_themes[0].PosCenter.rotY = 0.f;
	m_themes[0].PosCenter.rotZ = 0.f;

	m_themes[0].Deca.x = 1.6f;
	m_themes[0].Deca.y = 0.0f;
	m_themes[0].Deca.z = 0.f;

	m_themes[0].Deca.rotX = 0.f;
	m_themes[0].Deca.rotY = 1.5f;
	m_themes[0].Deca.rotZ = 0.f;
	m_themes[0].speed = 0.05f;
	
	m_themes[0].PosTxt.x = 1.6f;
	m_themes[0].PosTxt.y = -1.0f;
	m_themes[0].PosTxt.z = 3.f;

	m_themes[0].PosTxt.rotX = 0.f;
	m_themes[0].PosTxt.rotY = 0.f;
	m_themes[0].PosTxt.rotZ = 0.f;

	// Pyramide
	m_themes[1].PosCenter.x = 0.f;
	m_themes[1].PosCenter.y = 0.8f;
	m_themes[1].PosCenter.z = 5.f;

	m_themes[1].PosCenter.rotX = 0.f;
	m_themes[1].PosCenter.rotY = 0.f;
	m_themes[1].PosCenter.rotZ = 0.f;

	m_themes[1].Deca.x = 2.8f;
	m_themes[1].Deca.y = 0.0f;
	m_themes[1].Deca.z = -2.f;

	m_themes[1].Deca.rotX = 0.f;
	m_themes[1].Deca.rotY = 0.0f;
	m_themes[1].Deca.rotZ = 0.f;
	m_themes[1].speed = 0.05f;

	m_themes[1].PosTxt.x = 1.6f;
	m_themes[1].PosTxt.y = -1.0f;
	m_themes[1].PosTxt.z = 3.f;
			 
	m_themes[1].PosTxt.rotX = 0.f;
	m_themes[1].PosTxt.rotY = 0.f;
	m_themes[1].PosTxt.rotZ = 0.f;

	// Flat
	m_themes[2].PosCenter.x = 0.f;
	m_themes[2].PosCenter.y = 0.8f;
	m_themes[2].PosCenter.z = 5.f;
				 
	m_themes[2].PosCenter.rotX = 0.f;
	m_themes[2].PosCenter.rotY = 0.f;
	m_themes[2].PosCenter.rotZ = 0.f;
				 
	m_themes[2].Deca.x = 2.1f;
	m_themes[2].Deca.y = 0.0f;
	m_themes[2].Deca.z = 0.f;
				 
	m_themes[2].Deca.rotX = 0.f;
	m_themes[2].Deca.rotY = 0.0f;
	m_themes[2].Deca.rotZ = 0.f;
	m_themes[2].speed = 0.05f;

	m_themes[2].PosTxt.x = 0.f;
	m_themes[2].PosTxt.y = -1.0f;
	m_themes[2].PosTxt.z = 0.f;
			 
	m_themes[2].PosTxt.rotX = 0.f;
	m_themes[2].PosTxt.rotY = 0.f;
	m_themes[2].PosTxt.rotZ = 0.f;

	// Almost Fullscreen ...
	m_themes[3].PosCenter.x = 0.f;
	m_themes[3].PosCenter.y = 0.f;
	m_themes[3].PosCenter.z = -1.2f;
				 
	m_themes[3].PosCenter.rotX = 0.f;
	m_themes[3].PosCenter.rotY = 0.f;
	m_themes[3].PosCenter.rotZ = 0.f;
				 
	m_themes[3].Deca.x = 5.f;
	m_themes[3].Deca.y = 0.0f;
	m_themes[3].Deca.z = 1.f;
				 
	m_themes[3].Deca.rotX = 0.f;
	m_themes[3].Deca.rotY = 0.0f;
	m_themes[3].Deca.rotZ = 0.f;
	m_themes[3].speed = 0.07f;

	m_themes[3].PosTxt.x = 1.6f;
	m_themes[3].PosTxt.y = -1.0f;
	m_themes[3].PosTxt.z = 0.f;
			 
	m_themes[3].PosTxt.rotX = 0.f;
	m_themes[3].PosTxt.rotY = 0.f;
	m_themes[3].PosTxt.rotZ = 0.f;

	// Big ...
	m_themes[4].PosCenter.x = -0.3f;
	m_themes[4].PosCenter.y = 0.f;
	m_themes[4].PosCenter.z = 0.f;
				 
	m_themes[4].PosCenter.rotX = 0.1f;
	m_themes[4].PosCenter.rotY = -0.8f;
	m_themes[4].PosCenter.rotZ = 0.f;
				 
	m_themes[4].Deca.x = 5.f;
	m_themes[4].Deca.y = 0.0f;
	m_themes[4].Deca.z = 1.f;
				 
	m_themes[4].Deca.rotX = 0.f;
	m_themes[4].Deca.rotY = 0.0f;
	m_themes[4].Deca.rotZ = 0.f;
	m_themes[4].speed = 0.07f;

	m_themes[4].PosTxt.x = 1.6f;
	m_themes[4].PosTxt.y = -1.0f;
	m_themes[4].PosTxt.z = 0.f;
			 
	m_themes[4].PosTxt.rotX = 0.f;
	m_themes[4].PosTxt.rotY = 1.5f;
	m_themes[4].PosTxt.rotZ = 0.f;
}

#define POS_ANIMEF(val) {\
	float anim_speed = (from->val-to->val)*theme_speed; \
	if(from->val < to->val){ \
		from->val -=anim_speed; \
	} \
	else if(from->val > to->val){ \
		from->val -=anim_speed; \
	}\
}

void Video::Animate(Pos * from, Pos * to){
	//float anim_speed = 0.1f;

	float theme_speed = GetTheme()->speed;
	
	fcs=cs;

	POS_ANIMEF(x)
	POS_ANIMEF(y)
	POS_ANIMEF(z)
	POS_ANIMEF(rotX)
	POS_ANIMEF(rotY)
	POS_ANIMEF(rotZ)
}

int Video::Animate(std::vector <Game>::iterator game, int i){
	int gLength = g_GameList.Length();

	Pos pos;
	
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	pos.rotX = 0;
	pos.rotY = 0;
	pos.rotZ = 0;

	float mul_pos = (((float)i)-fcs);
	float mul_rot = mul_pos;

	pos.x = GetTheme()->PosCenter.x + ( GetTheme()->Deca.x * mul_pos ); // + (i==1)?1:0;
	pos.y = GetTheme()->PosCenter.y + ( GetTheme()->Deca.y * mul_pos );

	// Rotation
	pos.rotX = GetTheme()->PosCenter.rotX +( GetTheme()->Deca.rotX * mul_rot );
	pos.rotY = GetTheme()->PosCenter.rotY +( GetTheme()->Deca.rotY * mul_rot );
	pos.rotZ = GetTheme()->PosCenter.rotZ +( GetTheme()->Deca.rotZ * mul_rot );

	// Translation
	if(mul_pos<0){
		pos.z = GetTheme()->PosCenter.z + ( GetTheme()->Deca.z * mul_pos);
	}
	else if(mul_pos>0){
		pos.z = GetTheme()->PosCenter.z - ( GetTheme()->Deca.z * mul_pos);
	}
	else{
		pos.z = GetTheme()->PosCenter.z;
	}

	// Clamp Rotation
	if(pos.rotY < (GetTheme()->PosCenter.rotY + (GetTheme()->Deca.rotY * -1.0f))){
		pos.rotY = GetTheme()->PosCenter.rotY + ( GetTheme()->Deca.rotY * -1.0f );
	}
	else if(pos.rotY > (GetTheme()->PosCenter.rotY + (GetTheme()->Deca.rotY * 1.0f))){
		pos.rotY = GetTheme()->PosCenter.rotY +( GetTheme()->Deca.rotY * 1.0f );
	}

	Animate(&game->position,&pos);
	return 0;
}

int Video::DrawGame(std::vector <Game>::iterator game, int i){
	// Draw Cover
	DrawTexture(
		game->texture, 
		game->position.x,game->position.y,game->position.z,
		game->position.rotX,game->position.rotY,game->position.rotZ
	);

	if(i==cs){
		// Draw text
		Themes *curTheme =  Video::GetTheme();
		DrawTexture(game->name_texture,
			curTheme->PosTxt.x,curTheme->PosTxt.y,curTheme->PosTxt.z,
			curTheme->PosTxt.rotX,curTheme->PosTxt.rotY,curTheme->PosTxt.rotZ
		);
	}

	return 0;
}

/**
Order : rotate -> translate
**/
void Video::DrawTexture(LPDIRECT3DTEXTURE9 tex, float posX, float posY, float posZ, float rotX, float rotY, float rotZ){

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHAREF, 0x08 );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	// Translation
	XMMATRIX Translation = XMMatrixTranslation(posX,posY,posZ);
	
	// Rotation
	// XMMATRIX Rotation = ( XMMatrixRotationX(rotX) * XMMatrixRotationY(rotY) * XMMatrixRotationZ(rotZ) ) ;	
	XMMATRIX Rotation = ( XMMatrixRotationRollPitchYaw( (rotX), (rotY), (rotZ)) ) ;

	XMMATRIX matWorld = Rotation * Translation;

	matWVP = matWorld * matView * matProj;

	// Draw Model
	g_pd3dDevice->SetVertexDeclaration( g_pVertexDecl );
	g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( VertexFormat ) );
	g_pd3dDevice->SetVertexShaderConstantF( 0, ( float* )&matWVP, 4 );
	g_pd3dDevice->SetTexture(0,tex);
	g_pd3dDevice->SetVertexShader( g_pVertexShader );
    g_pd3dDevice->SetPixelShader( g_pPixelShader );

	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	// Draw Reflexion
	// Compute reflexion
	Translation = XMMatrixTranslation(posX,posY,posZ);
	Rotation = ( XMMatrixRotationRollPitchYaw( (rotX), (rotY), (rotZ)) ) ;
	
	XMVECTOR v = {0,1,0};

	matWorld = XMMatrixTranslation(0,-2.0f,0) * Rotation * Translation  ;

	matWVP = matWorld * matView * matProj;

	g_pd3dDevice->SetVertexDeclaration( g_pVertexDecl );
	g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( VertexFormat ) );
	g_pd3dDevice->SetVertexShaderConstantF( 0, ( float* )&matWVP, 4 );
	g_pd3dDevice->SetTexture(0,tex);
	g_pd3dDevice->SetVertexShader( g_pVertexShader );
    g_pd3dDevice->SetPixelShader( g_pPixelShaderReflexion );

	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}


void Video::Render(){

	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		g_GameList.ExecCallback(Animate);
		g_GameList.ExecCallback(DrawGame);

		g_pd3dDevice->EndScene();
	}	

	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	HardwareManager::Update();

	// update time - used for animation ...
	video_time+=0.1f;
}


HRESULT Video::CompileShaders(){

	// Buffers to hold compiled shaders and possible error messages
	ID3DXBuffer* pShaderCode = NULL;
	ID3DXBuffer* pErrorMsg = NULL;

	// Compile vertex shader.
	HRESULT hr = D3DXCompileShader( g_strVertexShaderProgram, ( UINT )strlen( g_strVertexShaderProgram ),
									NULL, NULL, "main", "vs_2_0", 0,
									&pShaderCode, &pErrorMsg, NULL );
	if( FAILED( hr ) )
	{
		OutputDebugStringA( pErrorMsg ? ( CHAR* )pErrorMsg->GetBufferPointer() : "" );
		return E_FAIL;
	}

	// Create vertex shader.
	g_pd3dDevice->CreateVertexShader( ( DWORD* )pShaderCode->GetBufferPointer(),
										&g_pVertexShader );

	// Shader code is no longer required.
	pShaderCode->Release();
	pShaderCode = NULL;

	// Compile pixel shader.
	hr = D3DXCompileShader( g_strPixelShaderProgram, ( UINT )strlen( g_strPixelShaderProgram ),
							NULL, NULL, "main", "ps_2_0", 0,
							&pShaderCode, &pErrorMsg, NULL );
	if( FAILED( hr ) )
	{
		OutputDebugStringA( pErrorMsg ? ( CHAR* )pErrorMsg->GetBufferPointer() : "" );
		return E_FAIL;
	}

	// Create pixel shader.
	g_pd3dDevice->CreatePixelShader( ( DWORD* )pShaderCode->GetBufferPointer(),
										&g_pPixelShader );

	// Shader code no longer required.
	pShaderCode->Release();
	pShaderCode = NULL;


	// Compile pixel reflexion shader.
	hr = D3DXCompileShader( g_strPixelRShaderProgram, ( UINT )strlen( g_strPixelRShaderProgram ),
							NULL, NULL, "main", "ps_2_0", 0,
							&pShaderCode, &pErrorMsg, NULL );
	if( FAILED( hr ) )
	{
		OutputDebugStringA( pErrorMsg ? ( CHAR* )pErrorMsg->GetBufferPointer() : "" );
		return E_FAIL;
	}

	// Create pixel reflexion shader.
	g_pd3dDevice->CreatePixelShader( ( DWORD* )pShaderCode->GetBufferPointer(),
		&g_pPixelShaderReflexion );

	// Shader code no longer required.
	pShaderCode->Release();
	pShaderCode = NULL;


	// Define the vertex elements.
	static const D3DVERTEXELEMENT9 VertexElements[3] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,    0 },
		D3DDECL_END()
	};

	// Create a vertex declaration from the element descriptions.
	g_pd3dDevice->CreateVertexDeclaration( VertexElements, &g_pVertexDecl );

	ATG::g_pd3dDevice =  (ATG::D3DDevice*)g_pd3dDevice;
	// Load Font
	vFont.Create( "game:\\Media\\Fonts\\Arial_16.xpr" );
	vFont.SetWindow( ATG::GetTitleSafeArea() );

	return S_OK;
}

LPDIRECT3DTEXTURE9 Video::CreateFontTexture(const char * str){
	int Size = MultiByteToWideChar (CP_ACP, 0, str, -1, NULL, 0);
	LPWSTR wUnicode = new WCHAR[Size];
	MultiByteToWideChar (CP_ACP, 0, str, -1, wUnicode, Size);
	
	return vFont.CreateTexture(wUnicode);
};

LPDIRECT3DTEXTURE9 Video::LoadTextureFromFile(std::string filename){

	LPDIRECT3DTEXTURE9 tex=NULL;

	HRESULT hr= D3DXCreateTextureFromFileExA( 
		g_pd3dDevice,
		filename.c_str(), 
		D3DX_DEFAULT,
		D3DX_DEFAULT, 
		1,
		0, 
		D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED , 
		D3DX_FILTER_BOX, 
		D3DX_FILTER_BOX, 
		0, 
		NULL, 
		NULL, 
		&tex
	);

	return tex;
}

HRESULT Video::SaveTextureDDS(LPDIRECT3DTEXTURE9 pTexture, std::string filename){
	return D3DXSaveTextureToFile(
		filename.c_str(),
		D3DXIFF_DDS,
		pTexture,
		NULL
		);
}