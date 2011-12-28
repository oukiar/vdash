#pragma once

#include "include.h"
#include <vector>
#include <string>
#include "src/fsd/XeXtractor.h"

enum {
	G_XEX,
	G_LIVE,
	G_ELF
};

struct Pos{
	float x,y,z;
	float rotX,rotY,rotZ;
};

typedef struct Game{
	std::string path;
	std::string name; // not utf8
	std::string texture_filename;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 name_texture;
	XEX_EXECUTION_ID XEX;
	int type;
	Pos position;
} Game;

typedef int (*GameListCallback)(std::vector <Game>::iterator, int i);

class GameList
{
private:
	std::vector <Game> m_GameList;
	std::vector <std::string> m_PathList;
public:
	//
	void AddGame(Game * game);
	void AddGame(Game game);
	void AddGame(std::string name,std::string path, LPDIRECT3DTEXTURE9 texture, int type);
	void AddGame(std::string name,std::string path, std::string nexart_path, int type);

	Game at(int i){
		return m_GameList.at(i);
	}

	int Length(){
		return m_GameList.size();
	}

	void ExecCallback(GameListCallback func);
	//
	void AddDirToScanList(std::string dir){
		m_PathList.push_back(dir);
	};
	void Scan();

	//
	HRESULT LoadList();
	HRESULT SaveList();
	//
	HRESULT LoadRessource();
	//
	GameList(void){
		m_GameList.reserve(500);
	};
	~GameList(void){
		
	};
};

extern GameList g_GameList;