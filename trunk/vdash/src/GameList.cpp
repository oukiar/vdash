#include "StdAfx.h"
#include "GameList.h"
#include "Video.h"
#include "Mount.h"
#include "Scan.h"

#include <algorithm>

GameList g_GameList;

enum sort_order{
	SORT_BY_NAME,
	SORT_BY_TYPE,
	SORT_BY_PATH
};

static bool sort_by_name( const Game &lhs, const Game & rhs )
{
	return lhs.name < rhs.name;
}

static bool sort_by_type( const Game &lhs, const Game & rhs )
{
	return lhs.type < rhs.type;
}

static bool sort_by_path( const Game &lhs, const Game & rhs )
{
	return lhs.path < rhs.path;
}

void GameList::SortByName(){
	sort_order = SORT_BY_NAME;
	Sort();
};
void GameList::SortByType(){
	sort_order = SORT_BY_TYPE;
	Sort();
};
void GameList::SortByPath(){
	sort_order = SORT_BY_PATH;
	Sort();
};

void GameList::Sort(){
	switch(sort_order){
		case SORT_BY_NAME:
			sort (m_GameList.begin(), m_GameList.end(),sort_by_name);
			break;
		case SORT_BY_TYPE:
			sort (m_GameList.begin(), m_GameList.end(),sort_by_type);
			break;
		case SORT_BY_PATH:
			sort (m_GameList.begin(), m_GameList.end(),sort_by_path);
			break;
	}	
}

HRESULT GameList::LoadList(){
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
	Sort();
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