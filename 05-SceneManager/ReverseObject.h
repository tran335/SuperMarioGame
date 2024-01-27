#pragma once
#include "GameObject.h"
#include "PlayScene.h"
#include "debug.h"
#include "Koopas.h"
#include "Platform.h"

#define REVERSEOBJECT_BBOX_WIDTH 48
#define REVERSEOBJECT_BBOX_HEIGHT 48

#define REVERSEOBJECT_AY 0.003f


class CReverseObject : public CGameObject
{
public:
	float ay;
	int isFall;
	LPGAMEOBJECT player;
	CReverseObject(float x, float y);
	virtual int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int getIsFall() { return this->isFall; }
};

