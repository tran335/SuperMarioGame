#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_THREE 232

#define	THREE_WIDTH 48
#define THREE_BBOX_WIDTH 48
#define THREE_BBOX_HEIGHT 48

class CThree : public CGameObject {
public:
	CThree(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

