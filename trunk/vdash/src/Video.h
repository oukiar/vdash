#pragma once

#include "include.h"
#include "GameList.h"
#include "HardwareManager.h"

struct Themes{
	// Position Centre
	Pos PosCenter;
	// Position between model
	Pos Deca;
	// Position between left/right near to center model
	Pos PosDC;
	// text position
	Pos PosTxt;

	float speed;
};


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
// Used to create the D3DDevice
extern LPDIRECT3D9             g_pD3D; 
// Our rendering device
extern LPDIRECT3DDEVICE9       g_pd3dDevice; 
// Buffer to hold MM
extern LPDIRECT3DVERTEXBUFFER9 g_pVB; 

extern XMMATRIX matWVP, matView, matProj;

extern IDirect3DPixelShader9* g_pPixelShaderReflexion;
extern IDirect3DPixelShader9* g_pPixelShader;
extern IDirect3DVertexShader9* g_pVertexShader;

extern IDirect3DVertexDeclaration9* g_pVertexDecl;

struct VertexFormat{
	float x,y,z,w;
	float u,v;
};

extern Themes m_themes[5];
extern int cs;

class Video
{
private:
public:
	static void MoveLeft();
	static void MoveRight();
	static void MoveUp();
	static void MoveDown();

	static void Animate(Pos * from, Pos * to);

	static Themes * GetTheme();

	static void InitDefaultThemes();

	static HRESULT InitVB(){
		if(FAILED(g_pd3dDevice->CreateVertexBuffer(4*sizeof(VertexFormat),0,0,D3DPOOL_DEFAULT, &g_pVB, NULL))){
			return E_FAIL;
		}

		VertexFormat v[]={
			//square
			//  X  /   Y  /  Z  /  W  /  U  /  V
			{ -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f },//1
			{ -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f },//2
			{  1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f }, //4
			{  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f },//3
		};

		VOID* pMM;
		if( FAILED( g_pVB->Lock( 0, sizeof( v ), ( void** )&pMM, 0 ) ) )
			return E_FAIL;
		memcpy( pMM, v, sizeof( v ) );
		g_pVB->Unlock();

		g_pd3dDevice->SetStreamSource(0,g_pVB,0,sizeof(VertexFormat));
		g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		return S_OK;
	}

	static HRESULT InitMatrices(){

		 // World matrix (identity in this sample)
		XMMATRIX matWorld = XMMatrixIdentity();

		// View matrix
		XMVECTOR vEyePt = XMVectorSet( 0.0f, 0.0f, -4.0f, 0.0f );
		XMVECTOR vLookatPt = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
		XMVECTOR vUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		matView = XMMatrixLookAtLH( vEyePt, vLookatPt, vUp );

		// Determine the aspect ratio
		//float fAspectRatio = ( float )HardwareManager::GetWidth() / ( float )HardwareManager::GetHeight();

		float fAspectRatio = 1.0f;

		// Projection matrix
		matProj = XMMatrixPerspectiveFovLH( XM_PI / 4, fAspectRatio, 0.f, 200.0f );

		// World*view*projection
		matWVP = matWorld * matView * matProj;

		return S_OK;
	}

	static HRESULT CompileShaders();

	static int Animate(std::vector <Game>::iterator game, int i);
	static int DrawGame(std::vector <Game>::iterator game, int i);
	static void DrawTexture(LPDIRECT3DTEXTURE9 tex, float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
	static void Render();


	static LPDIRECT3DTEXTURE9 CreateFontTexture(const char * str);
	static LPDIRECT3DTEXTURE9 LoadTextureFromFile(std::string filename);
	static HRESULT SaveTextureDDS(LPDIRECT3DTEXTURE9 pTexture, std::string filename);
};

