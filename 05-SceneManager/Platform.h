#pragma once

#include "GameObject.h"

#define PLATFORM_BBOX_WIDTH 48
#define PLATFORM_BBOX_HEIGHT 48

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	float x, y, width,height;

public: 
	CPlatform(float x, float y, float width, float height);

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	//int IsDirectionColliable(float nx, float ny);
};

typedef CPlatform* LPPLATFORM;