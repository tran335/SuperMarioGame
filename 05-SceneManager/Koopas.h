#pragma once
#include "GameObject.h"
#include "KoopasBound.h"
#include "Mario.h"
#include "Questionbrick.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.07f
#define KOOPAS_SLIDE_SPEED 0.5f

#define KOOPAS_BBOX_WIDTH 51
#define KOOPAS_BBOX_HEIGHT 79
#define KOOPAS_BBOX_HEIGHT_DIE 42

#define KOOPAS_DIE_TIMEOUT 500

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_SLIDE 300

#define ID_ANI_KOOPAS_WALKING_LEFT 301
#define ID_ANI_KOOPAS_WALKING_RIGHT 302 
#define ID_ANI_KOOPAS_DIE 303
#define ID_ANI_KOOPA_WAKING 305
#define ID_ANI_KOOPA_SLIDE 304

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	CMario* mario = NULL;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

    void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
	int IsDirectionColliable(float nx, float ny) { return 1; };
	void setPositionSlide();
};

