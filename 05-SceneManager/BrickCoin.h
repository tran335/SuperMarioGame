#pragma once
#include "GameObject.h"
#include "Questionbrick.h"

#define ID_ANI_BRICKCOIN 7100

#define BRICKCOIN_JUMP_SPEED_Y		0.4f
#define BRICKCOIN_RETURN_START_POS_VY 0.2f

#define JUMP_TIME 400
#define DROP_TIME 300

#define BRICKCOIN_MIN_Y 20
#define BRICKCOIN_MAX_Y 150


#define BRICKCOIN_BBOX_WIDTH 48
#define BRICKCOIN_BBOX_HEIGHT 48

#define BRICKCOIN_STATE_THROW_UP 710

class CBrickCoin : public CGameObject
{
	float start_y;
	float jumpTime = 0;
	float dropTime = 0;
	float x, y;
	bool isDrop = false;
public:
	CBrickCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual int IsBlocking() { return 0; };
	void BrickStartToThrow() { jumpTime = GetTickCount64();};
	void BrickStartToDrop() { dropTime = GetTickCount64(); };
	void SetState(int state);
};

