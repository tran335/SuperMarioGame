#pragma once
#include "GameObject.h"
#include "CameraBound.h"
#include "Mario.h"


#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.1f
#define GOOMBA_KICK_BY_KOOPAS_SPEED 0.6f
#define GOOMBA_KICK_BY_RACCOON_SPEED 0.8f

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 40
#define GOOMBA_BBOX_HEIGHT_DIE 25

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_KICK_BY_KOOPAS 300
#define GOOMBA_STATE_KICK_BY_RACCOON 400

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_KICK_BY_KOOPAS 5002

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	float start_x;
	float start_y;
	
	ULONGLONG die_start;
	ULONGLONG reset_time;
	BOOLEAN isfinddropdirection;
	BOOLEAN isBack;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();

	int IsCollidable() { return (state!=GOOMBA_STATE_KICK_BY_KOOPAS && state != GOOMBA_STATE_KICK_BY_RACCOON && state != GOOMBA_STATE_DIE && !isBack); };
	int IsBlocking() { return (state != GOOMBA_STATE_KICK_BY_KOOPAS && state != GOOMBA_STATE_KICK_BY_RACCOON && state != GOOMBA_STATE_DIE); }
	virtual void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);

	//void startfinddropdirecttion();

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};