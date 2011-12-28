#include "StdAfx.h"
#include "GameList.h"
#include "Video.h"
#include "Mount.h"
#include "Scan.h"

GameList g_GameList;

// 15668 -> 3 thread
// 14906 -> 2 thread
// 26761 -> 1 threaded 
// 29382 -> 1 threaded + lock xex
// 37004 -> no thread
HRESULT GameList::LoadList(){
	//AddFolderToScan("hdd1:\\DEVKIT");
	AddFolderToScan("hdd1:");
	AddFolderToScan("usb0:");

	DWORD start = GetTickCount();

	ScanFolder();

	DWORD end = GetTickCount();

	printf("LoadList %d\r\n",end-start);

	return S_OK;
};


void GameList::ExecCallback(GameListCallback func){
		std::vector <Game>::iterator it;
		int i = 0;
		for ( it=m_GameList.begin() ; it < m_GameList.end(); it++ ){
			// maybe we miss something to it here ...
			if(it->name_texture == NULL)
				it->name_texture = Video::CreateFontTexture(it->name.c_str());
			func(it,i++);
		}
	}

HRESULT GameList::LoadRessource(){
	return S_OK;
	// run in a thread !!
	printf("Load Ressource\r\n");
	DWORD start = GetTickCount();

	std::vector <Game>::iterator it;
	int i = 0;
	for ( it=m_GameList.begin() ; it < m_GameList.end(); it++ ){
		
		// create font texture
		if(!it->name_texture){
			it->name_texture = Video::CreateFontTexture(it->name.c_str());
		}
	}

	DWORD end = GetTickCount();

	printf("LoadRessource %d\r\n",end-start);
	return S_OK;
}


void GameList::AddGame(Game game){
	memset(&game.position,0,sizeof(Pos));
	m_GameList.push_back(game);	
};

void GameList::AddGame(std::string name,std::string path, std::string nexart_path, int type){
	Game game;
	game.name = name;
	game.path = path;
	game.texture_filename = nexart_path;

	game.texture = NULL;
	game.name_texture = NULL;
	//game.name_texture = Video::CreateFontTexture(name.c_str());


	game.type = type;

	AddGame(game);
}



void GameList::AddGame(std::string name,std::string path, LPDIRECT3DTEXTURE9 texture, int type){
	Game game;
	game.name = name;
	game.path = path;

	game.texture = texture;
	game.name_texture = NULL;
	//game.name_texture = Video::CreateFontTexture(name.c_str());

	game.type = type;

	AddGame(game);
}

void GameList::AddGame(Game * game){
	Game copie;
	memcpy(&copie,game,sizeof(Game));
	AddGame(copie);
}