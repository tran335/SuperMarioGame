#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COINBRICK 1900
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48

class CCoinBrick : public CGameObject {
public:
	CCoinBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};