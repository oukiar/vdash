#include "stdafx.h"
#include "Video.h"
#include "HardwareManager.h"
#include "GameList.h"

#if 0
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT ){
	HardwareManager::InitSystem();
	HardwareManager::InitD3D();
	//HardwareManager::LoadFile();

	g_GameList.LoadList();

	Video::InitDefaultThemes();
	Video::InitVB();
	Video::InitMatrices();
	Video::CompileShaders();

	while(1){
		Video::Render();
	}

	HardwareManager::Cleanup();
}
#endif