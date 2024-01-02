#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Mario.h"

#define ID_ANI_POWER_0 1800
#define ID_ANI_POWER_1 1801
#define ID_ANI_POWER_2 1802
#define ID_ANI_POWER_3 1803
#define ID_ANI_POWER_4 1804
#define ID_ANI_POWER_5 1805
#define ID_ANI_POWER_6 1806

#define VX_1 0.4f
#define VX_2 0.45f
#define VX_3 0.5f
#define VX_4 0.55f
#define VX_5 0.6f
#define VX_6 0.65f

#define POWER_CX 270
#define POWER_CY 600


class Power : public CGameObject
{
protected:
	float x;
	float y;
	CMario* mario;
public:
	Power(float x, float y);
	void Update();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0; t = 0; r = 0; b = 0; };
};

