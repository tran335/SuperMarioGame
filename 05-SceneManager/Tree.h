#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TREE 202
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48

class CTree : public CGameObject {
public:
	CTree(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};