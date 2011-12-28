// vdash.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "Video.h"
#include "HardwareManager.h"
#include "GameList.h"
#include "SimpleIni.h"

void tScan(){
	
};


void LoadConfig(){
	CSimpleIniA ini(true, true, true);
	SI_Error rc = ini.LoadFile("game:\\config.ini");
    if (rc < 0) return;
	
}

bool SaveConfig(){
	CSimpleIniA ini(true, true, true);

	SI_Error rc;
	rc = ini.LoadFile("game:\\config.ini");

	for(int i = 0;i<5;i++){
		Themes * curTheme = &m_themes[i];
		char section[10];
		sprintf(section,"theme_%d",i);
		printf("%s\r\n",section);
		// Add settings ...
		//rc = ini.SetValue(section, "PosCenter_x", curTheme->PosCenter.x);
		rc = ini.SetDoubleValue(section, "PosCenter_x", curTheme->PosCenter.x);
	}

	rc = ini.SaveFile("game:\\config.ini",true);
	if (rc < 0) 
		return false;

	return true;
}

//-------------------------------------------------------------------------------------
// Name: main()
// Desc: The application's entry point
//-------------------------------------------------------------------------------------
void __cdecl main()
{
	HardwareManager::InitSystem();
	HardwareManager::InitD3D();

	Video::InitDefaultThemes();
	Video::InitVB();
	Video::InitMatrices();
	Video::CompileShaders();

	g_GameList.LoadList();
	g_GameList.LoadRessource();
	
	while(1){
		Video::Render();
	}

	HardwareManager::Cleanup();
}

