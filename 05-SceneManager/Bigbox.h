#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

#define BIGBOX_WIDTH 48
#define BIGBOX_HEIGHT 48

class CBigbox : public CGameObject
{
protected:
	float x, y, width, height;
public:
	CBigbox(float x, float y, float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny);
};

