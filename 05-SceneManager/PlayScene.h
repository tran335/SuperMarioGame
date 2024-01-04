#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "Bigbox.h"
#include "MapPipe.h"
#include "VenusFireTrap.h"
#include "Koopas.h"
#include "CameraBound.h"
#include "Hud.h"

#define ADD_CY 50
#define INTRO_SCENE 3
#define OVERWORLD_SCENE 2
#define WORLD_MAP_1_1_SCENE 1

class CPlayScene: public CScene
{
//protected: 
public:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;
	CMap* map;
	CMapPipe* map_pipe;
	Hud* hud;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_MAPPIPE(string line);
	void _ParseSection_HUD(string line);
	void LoadAssets(LPCWSTR assetFile);
	
//public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();


	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

