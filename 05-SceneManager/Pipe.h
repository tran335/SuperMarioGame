#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

#define PIPE_WIDTH 48
#define PIPE_HEIGHT 48

class CPipe : public CGameObject
{
protected:
	float x, y, width, height;
public:
	CPipe(float x, float y, float width, float height);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny);
};

