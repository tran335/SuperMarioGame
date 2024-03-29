#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Questionbrick.h"
#include "Koopas.h"
#include "KoopasBound.h"
#include "BrickCoin.h"
#include "ParaGoomba.h"
#include "ReverseObject.h"
#include "Parakoopa.h"
#include "Piranha.h"
#include "Tree.h"
#include "Node.h"
#include "InOut.h"
#include "Pipe.h"
#include "Three.h"

#include "MarioOverworld.h"
#include "SampleKeyEventHandler.h"
#include "IntroKeyHandler.h"
#include "OverworldKeyHandler.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	switch (id)
	{
	case INTRO_SCENE:
		key_handler = new CIntroKeyHandler(this);
		break;
	case OVERWORLD_SCENE:
		key_handler = new COverworldKeyHandler(this);
		break;
	case WORLD_MAP_1_1_SCENE:
		key_handler = new CSampleKeyHandler(this);
		break;
	}
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAP	3
#define SCENE_SECTION_MAPPIPE	4
#define SCENE_SECTION_HUD	5

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		if (id == OVERWORLD_SCENE) {
			obj = new CMarioOverworld(x, y);
			player = (CMarioOverworld*)obj;
		}
		else {
			obj = new CMario(x, y);
			player = (CMario*)obj;
		}

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_PARAGOOMBA: obj = new CParaGoomba(x, y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COINBRICK: obj = new CCoinBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_PIRANHA: obj = new CPiranha(x, y); break;
	case OBJECT_TYPE_THREE: obj = new CThree(x, y); break;
	case OBJECT_TYPE_PLATFORM:
	{

		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CPlatform(x, y, width, height);

		break;
	}
	case OBJECT_TYPE_BIGBOX:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CBigbox(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_INOUT:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CInOut(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CPipe(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_QUESTIONBRICK:
	{
		int item_type = atoi(tokens[3].c_str());
		
		/*if (item_type == 1) {
			obj = new CBrickCoin(x, y);
			obj->SetPosition(x, y);
			objects.push_back(obj);
		}*/
		obj = new CQuestionbrick(x, y, item_type);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		
		break;
	}
	case OBJECT_TYPE_VENUSFIRETRAP:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CVenusFireTrap(x, y, type);
		break;
	}
	case OBJECT_TYPE_KOOPAS:
	{
		obj = new CKoopas(x, y);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PARAKOOPAS:
	{
		obj = new CParaKoopa(x, y);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_CAMMERABOUND:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CCameraBound(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_TREE:
	{
		obj = new CTree(x, y);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_NODE:
	{
		obj = new CNode(x, y);
		node = (CNode*)obj;
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_KOOPASBOUND:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		obj = new CKoopasBound(x, y, width, height);
		break;
	}
	/*case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;*/


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return; // skip invalid lines

	LPCWSTR mapFilePath = ToLPCWSTR(tokens[0].c_str());
	LPCWSTR tilesetFilePath = ToLPCWSTR(tokens[1].c_str());
	int texId = atoi(tokens[2].c_str());
	int width_map = atoi(tokens[3].c_str());
	int height_map = atoi(tokens[4].c_str());
	int columns = atoi(tokens[5].c_str());
	int rows = atoi(tokens[6].c_str());

	map = new CMap(mapFilePath, tilesetFilePath, texId, width_map, height_map, columns, rows);
	map->LoadResourceMap();

}
void CPlayScene::_ParseSection_HUD(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

    hud = new Hud(x, y); 
}

void CPlayScene::_ParseSection_MAPPIPE(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return; // skip invalid lines

	LPCWSTR mapFilePath = ToLPCWSTR(tokens[0].c_str());
	LPCWSTR tilesetFilePath = ToLPCWSTR(tokens[1].c_str());
	int texId = atoi(tokens[2].c_str());
	int width_map = atoi(tokens[3].c_str());
	int height_map = atoi(tokens[4].c_str());
	int columns = atoi(tokens[5].c_str());
	int rows = atoi(tokens[6].c_str());

	map_pipe = new CMapPipe(mapFilePath, tilesetFilePath, texId, width_map, height_map, columns, rows);
	map_pipe->LoadResourceMap();

}


void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; };
		if (line == "[MAPPIPE]") { section = SCENE_SECTION_MAPPIPE; continue; };
		if (line == "[HUD]") { section = SCENE_SECTION_HUD; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_MAPPIPE: _ParseSection_MAPPIPE(line); break;
			case SCENE_SECTION_HUD: _ParseSection_HUD(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	int start_cy = cy;
	CGame* game = CGame::GetInstance();

	if (id == WORLD_MAP_1_1_SCENE) {
		cx -= game->GetBackBufferWidth() / 2;


		if (cy <= game->GetBackBufferHeight() * 2 - start_cy) {
			cy -= game->GetBackBufferHeight() / 2;

		}
		else {
			if (cy > game->GetBackBufferHeight() * 4 - start_cy) {
				cy += game->GetBackBufferHeight() - start_cy / 1.65;
			}
			else
				cy = game->GetBackBufferHeight() + ADD_CY;
		}
	}
	else
	{
		cx = -game->GetBackBufferWidth();
		cy = ADD_CY_INTROSCENE;
	}

	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;

	CGame::GetInstance()->SetCamPos(cx, /*0.0f*/ cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	map->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();
	if (id != OVERWORLD_SCENE) {
		map_pipe->Render();
		if (id == WORLD_MAP_1_1_SCENE) {
			hud->Render();
		}
		
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	/*for (int i = 0; i < objects.size(); i++)
		delete objects[i];*/

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}



bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}