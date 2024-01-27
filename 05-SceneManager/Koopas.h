#pragma once
#include "GameObject.h"
#include "KoopasBound.h"
#include "Mario.h"
#include "Questionbrick.h"
#include "Items.h"
#include "ReverseObject.h"
#include "CameraBound.h"
#include "Goomba.h"
#include "Platform.h"
#include "CoinBrick.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.07f
#define KOOPAS_SLIDE_SPEED 0.5f

#define KOOPAS_BBOX_WIDTH 51
#define KOOPAS_BBOX_HEIGHT 79
#define KOOPAS_BBOX_HEIGHT_WAKE 49
#define KOOPAS_BBOX_HEIGHT_DIE 42

#define KOOPAS_DIE_TIMEOUT 5000
#define KOOPAS_WAKING_TIMEOUT 2000

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_SLIDE 300
#define KOOPAS_STATE_WAKING 400

#define ID_ANI_KOOPAS_WALKING_LEFT 301
#define ID_ANI_KOOPAS_WALKING_RIGHT 302 
#define ID_ANI_KOOPAS_DIE 303
#define ID_ANI_KOOPAS_WAKING 305
#define ID_ANI_KOOPAS_SLIDE 304

//Pickup by mario
#define MARIO_SMALL_HANDLED_WIDTH 23
#define MARIO_SMALL_HANDLED_HEIGHT 2

#define MARIO_BIG_HANDLED_WIDTH 25
#define MARIO_BIG_HANDLED_HEIGHT 10

#define MARIO_RACCOON_HANDLED_WIDTH 35
#define MARIO_RACCOON_HANDLED_HEIGHT 10


#define REVERSE_OBJECT_X 58

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	CMario* mario = NULL;

	ULONGLONG die_start;
	ULONGLONG waking_start;

	BOOLEAN isHandled = false;
	BOOLEAN isDrop;
	BOOLEAN isPlatform;
	BOOLEAN isOnPlatform;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int IsCollidable() { return (isDrop != true); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithCoinBrick(LPCOLLISIONEVENT e);
	//void OnCollisionWithReverseObject(LPCOLLISIONEVENT e);
	

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
	int IsDirectionColliable(float nx, float ny) { return 1; };
	void setPositionSlide();
	void startWakingTime() { waking_start = GetTickCount64(); }
	void HandledByMario();
	void HandledByMarioRelease();
	void setPositionByHandle();
};

