#pragma once
#include "GameObject.h"

#define CAMERABOUND_BBOX_WIDTH 48
#define CAMERABOUND_BBOX_HEIGHT 48
class CCameraBound : public CGameObject
{
protected:
	float x, y, width, height;

public:
	CCameraBound(float x, float y, float width, float height);

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

