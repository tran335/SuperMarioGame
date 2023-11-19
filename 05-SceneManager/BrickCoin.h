#pragma once
#include "GameObject.h"
#include "Questionbrick.h"

#define ID_ANI_BRICKCOIN 7100

class CBrickCoin : public CGameObject
{
	float x, y;
public:
	CBrickCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};

