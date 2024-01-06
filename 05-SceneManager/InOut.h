#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

#define INOUT_WIDTH 48
#define INOUT_HEIGHT 48

class CInOut : public CGameObject
{
protected:
	float x, y, width, height;
public:
	CInOut(float x, float y, float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny);
};

