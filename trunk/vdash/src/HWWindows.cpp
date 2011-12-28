#include "StdAfx.h"

#include "include.h"

#include "HardwareManager.h"
#include "Video.h"
#ifndef _XBOX
HWND hWnd;
static WNDCLASSEX _wc;

#define INSTANCE_NAME L"MDASH"
#define WINDOW_NAME L"MDASH Win7"

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static int i = D3DCMP_NEVER;



    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

		case WM_KEYDOWN:
			switch(wParam){
			case VK_RIGHT:
				{
					Video::MoveRight(); 
					break;
				}
			case VK_LEFT:
				{
					Video::MoveLeft();
					break;
				}

			case VK_UP:
				{
					Video::MoveUp();
					break;
				}
			case VK_DOWN:
				{
					Video::MoveDown();
					break;
				}
			}
    }

	if(i<D3DCMP_NEVER)
		i=D3DCMP_NEVER;

	if(i>D3DCMP_ALWAYS)
		i=D3DCMP_ALWAYS;

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

HRESULT HardwareManager::InitSystem(){

	// Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        INSTANCE_NAME, NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    hWnd = CreateWindowW( INSTANCE_NAME, WINDOW_NAME,
                              WS_OVERLAPPEDWINDOW, 100, 100, GetWidth(), GetHeight(),
                              NULL, NULL, wc.hInstance, NULL );

	//hide mouse 
	ShowCursor(SW_HIDE);

	// Show window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	_wc= wc;

	return S_OK;
}

void HardwareManager::Update(){

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	{
		MSG msg;
		ZeroMemory( &msg, sizeof( msg ) );

			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			
	}
}


HRESULT HardwareManager::InitD3D(){

	// Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    //d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//d3dpp.BackBufferWidth = 1280;
    //d3dpp.BackBufferHeight = 720;
    d3dpp.BackBufferFormat =  D3DFMT_A8R8G8B8;
   // d3dpp.FrontBufferFormat = D3DFMT_LE_X8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.BackBufferCount = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;



    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	

    // Device state would normally be set here
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);


	return S_OK;
}

HRESULT HardwareManager::Cleanup(){
	UnregisterClass( INSTANCE_NAME, _wc.hInstance );

	if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();

	return S_OK;
}

#else

#include "Mount.h"

void Add(char * d, char * mountpoint){
	Map(mountpoint,d);
}

HRESULT HardwareManager::InitSystem(){

	Add("\\Device\\Cdrom0","cdrom:");

	Add("\\Device\\Flash","flash:");
	
	//hdd
	Add("\\Device\\Harddisk0\\SystemPartition\\","hddx:");
	Add("\\Device\\Harddisk0\\Partition0","hdd0:");
	Add("\\Device\\Harddisk0\\Partition1","hdd1:");
	Add("\\Device\\Harddisk0\\Partition2","hdd2:");
	Add("\\Device\\Harddisk0\\Partition3","hdd3:");

	//mu
	Add("\\Device\\Mu0","mu0:");
	Add("\\Device\\Mu1","mu1:");
	Add("\\Device\\Mass0PartitionFile\\Storage","usbmu0:");

	//usb
	Add("\\Device\\Mass0", "usb0:");
	Add("\\Device\\Mass1", "usb1:");
	Add("\\Device\\Mass2", "usb2:");

	Add("\\Device\\BuiltInMuSfc","sfc:");

	return S_OK;
}


static XINPUT_STATE gamepad;
static XINPUT_STATE o_gamepad;

#define BTN(x) ( (gamepad.Gamepad.wButtons & x) && (!(o_gamepad.Gamepad.wButtons & x)))

void HardwareManager::Update(){
	int left,right,up,down;
	left=right=up=down=0;

	XInputGetState(0, &gamepad);

	if ( BTN (XINPUT_GAMEPAD_DPAD_RIGHT) ){
		Video::MoveRight(); 
	}
	if ( BTN (XINPUT_GAMEPAD_DPAD_LEFT) ){
		Video::MoveLeft(); 
	}
	if ( BTN (XINPUT_GAMEPAD_DPAD_UP) ){
		Video::MoveUp(); 
	}
	if ( BTN (XINPUT_GAMEPAD_DPAD_DOWN) ){
		Video::MoveDown(); 
	}
	if ( BTN (XINPUT_GAMEPAD_A) ){
		//
		XLaunchNewImage(g_GameList.at(cs).path.c_str(),0);
	}

	o_gamepad = gamepad;
}


HRESULT HardwareManager::InitD3D(){

	// Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );

    d3dpp.BackBufferWidth = 1280;
    d3dpp.BackBufferHeight = 720;
    d3dpp.BackBufferFormat =  ( D3DFORMAT )MAKESRGBFMT( D3DFMT_A8R8G8B8 );
    d3dpp.FrontBufferFormat = ( D3DFORMAT )MAKESRGBFMT( D3DFMT_LE_X8R8G8B8 );
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.BackBufferCount = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;



    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( 0, D3DDEVTYPE_HAL, NULL,
                                      NULL,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	

    // Device state would normally be set here
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);


	return S_OK;
}

HRESULT HardwareManager::Cleanup(){
	if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();

	return S_OK;
}

#endif