#pragma once
#include "GameObject.h"
#include "Questionbrick.h"

#define SUPERMUSHROOM_GRAVITY 0.001f

#define ITEMS_STATE_SUPERMUSHROOM 1
#define ITEMS_STATE_LEAF 2

#define ITEMS_BBOX_WIDTH 48
#define ITEMS_BBOX_HEIGHT 45

#define ID_ANI_SUPERMUSHROOM 120
#define SUPERMUSHROOM_WALKING_SPEED 0.05f

class CItems : public CGameObject
{
	float x, y, start_y, ax, ay;
	BOOLEAN isCollidable = true;
public:
	CItems(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionbrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	int IsCollidable() { return (isCollidable != false && state == ITEMS_STATE_SUPERMUSHROOM); };
	void SetState(int state);
};

