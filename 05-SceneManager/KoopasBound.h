#pragma once
#include "GameObject.h"
#include "Mario.h"

#define KOOPASBOUND_BBOX_WIDTH 48
#define KOOPASBOUND_BBOX_HEIGHT 48

class CKoopasBound : public CGameObject
{
protected:
	float x, y, width, height;
	BOOLEAN isColliable = NULL;
	CMario* mario = NULL;
	BOOLEAN c;

public:
	CKoopasBound(float x, float y, float width, float height);

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny);
	void getCollision(BOOLEAN c) { this->c = c; }
};

