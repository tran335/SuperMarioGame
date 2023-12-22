#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PIRANHA_BBOX_WIDTH 48
#define PIRANHA_BBOX_HEIGHT 73
#define PIRANHA_HEIGHT 73
#define PIRANHA_WIDTH 70
#define PIRANHA_HEIGHT_DOWN 20

// red VENUS
#define IC_ANI_PIRANHA 630

#define PIRANHA_SPEED 2.0f
#define GROW_UP_TIME 1000

class CPiranha : public CGameObject
{
	float width;
	float height;
	float start_y;
	float start_time;
	bool isStop = false;
	CMario* mario = NULL;
public:
	CPiranha(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void startTime() { start_time = GetTickCount64(); };
};
