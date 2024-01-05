#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

#define NODE_WIDTH 48
#define NODE_HEIGHT 48

class CNode : public CGameObject
{
protected:
	float x, y;
public:
	CNode(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};