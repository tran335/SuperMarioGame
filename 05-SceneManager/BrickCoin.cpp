#include "BrickCoin.h"

CBrickCoin::CBrickCoin(float x, float y)
{
	this->x = x;
	this->y = y;
	vy = -BRICKCOIN_JUMP_SPEED_Y;
}

void CBrickCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICKCOIN)->Render(x, y);
}

void CBrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy*dt;
	//vy = -BRICKCOIN_JUMP_SPEED_Y;

	if (jumpTime == 0) {
		BrickStartToThrow();
	}
	else if (GetTickCount64() - jumpTime > JUMP_TIME && jumpTime > 0) {
		if (GetTickCount64() - dropTime > DROP_TIME && dropTime > 0) {
			Delete();
			jumpTime = 0;
			dropTime = 0;

		}
		else {
			vy = BRICKCOIN_RETURN_START_POS_VY;
			if (dropTime == 0) {
				BrickStartToDrop();
			}
		}

	}

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}



