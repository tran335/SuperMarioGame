#pragma once
#include "GameObject.h"
#include "PlayScene.h"
#include "debug.h"
#include "Koopas.h"
#include "Platform.h"

#define REVERSEOBJECT_BBOX_WIDTH 48
#define REVERSEOBJECT_BBOX_HEIGHT 48


class CReverseObject : public CGameObject
{
public:
	CReverseObject(float x, float y);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

