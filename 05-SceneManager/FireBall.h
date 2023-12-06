#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"

#define ID_ANI_FIREBALL 110
#define FIREBALL_BBOX_WIDTH 25
#define FIREBALL_BBOX_HEIGHT 25
#define FIRE_BALL_SPEED_X 0.3f
#define FIRE_BALL_SPEED_Y 0.1f
#define FIREBALL_Y 10

#define UNFINDDIRECTION_TIME 500

#define FIREBALL_GRAVITY 0.00007f

class CFireBall : public CGameObject
{
	CMario* mario = NULL;
	float ax;
	float ay;
	ULONGLONG unfindslidedirecttion_time;
	BOOLEAN unfindslidedirecttion;
	BOOLEAN isCollision;

	ULONGLONG untouchable = 0;
	ULONGLONG untouchable_start = -1;

	//virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	//void OnCollisionWithMario(LPCOLLISIONEVENT e);
	//void OnCollisionWithPlatform(LPCOLLISIONEVENT e);

public:
	CFireBall(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void startfindslidedirecttion(DWORD dt);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
};
