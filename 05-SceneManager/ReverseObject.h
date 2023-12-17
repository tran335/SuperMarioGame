#pragma once
#include "GameObject.h"
#include "PlayScene.h"
#include "debug.h"

#define REVERSEOBJECT_BBOX_WIDTH 48
#define REVERSEOBJECT_BBOX_HEIGHT 48


class CReverseObject : public CGameObject
{
public:
	CReverseObject(float x, float y);
	virtual int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; };
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

