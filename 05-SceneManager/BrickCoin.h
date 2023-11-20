#pragma once
#include "GameObject.h"
#include "Questionbrick.h"
#include "Mario.h"

#define BRICKCOIN_STATE_THROWUP 710
#define ID_ANI_BRICKCOIN 7100
#define BRICKCOIN_BBOX_WIDTH 48
#define BRICKCOIN_BBOX_HEIGHT 46


class CBrickCoin : public CGameObject
{
	float x, y;
public:
	CBrickCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

};

