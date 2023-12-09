#pragma once
#include "GameObject.h"
#include "Questionbrick.h"

#include "Platform.h"
#include "CameraBound.h"
#include "Goomba.h"

#define SUPERMUSHROOM_GRAVITY_AX 0.005f
#define SUPERMUSHROOM_GRAVITY_AY 0.006f

#define LEAF_GRAVITY_AX 0.003f
#define LEAF_GRAVITY_AY 0.002f

#define MAX_Y 150

#define ITEMS_STATE_SUPERMUSHROOM 1
#define ITEMS_STATE_SUPERMUSHROOM_RIGHT 11
#define ITEMS_STATE_LEAF 2

#define ITEMS_BBOX_WIDTH 48
#define ITEMS_BBOX_HEIGHT 44

#define ID_ANI_SUPERMUSHROOM 120
#define ID_ANI_LEAF_LEFT 130
#define ID_ANI_LEAF_RIGHT 131
#define SUPERMUSHROOM_WALKING_SPEED 0.13f

#define DIRECT_TIME 1000

class CItems : public CGameObject
{
	float x, y, start_y, ax, ay, nx;
	BOOLEAN isCollidable = true;
	BOOLEAN isDirect = false;
	ULONGLONG direct_time;

public:
	CItems(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return (isCollidable != false && state != ITEMS_STATE_LEAF); };
	void SetState(int state);
	void startDirect() { direct_time = GetTickCount64(); isDirect = true; };
};

