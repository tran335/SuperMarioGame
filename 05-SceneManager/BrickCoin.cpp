#include "BrickCoin.h"

CBrickCoin::CBrickCoin(float x, float y)
{
	this->x = x;
	this->y = y;
	this->start_y = y;
}

void CBrickCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICKCOIN)->Render(x, y);
}

void CBrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy*dt;

	if (state == BRICKCOIN_STATE_THROW_UP && y < start_y - BRICKCOIN_MAX_Y) {
		vy = -vy;
	}
	else if (y >= start_y) {
		vy = 0;
		this->Delete();
	}


	//if (jumpTime == 0) {
	//	BrickStartToThrow();
	//}
	//else if (GetTickCount64() - jumpTime > JUMP_TIME && jumpTime > 0) {
	//	if (GetTickCount64() - dropTime > DROP_TIME && dropTime > 0) {
	//		this->Delete();
	//		jumpTime = 0;
	//		dropTime = 0;

	//	}
	//	else {
	//		vy = BRICKCOIN_RETURN_START_POS_VY;
	//		if (dropTime == 0) {
	//			BrickStartToDrop();
	//		}
	//	}

	//}

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICKCOIN_STATE_THROW_UP:
		vy = -BRICKCOIN_JUMP_SPEED_Y;
		break;
	}
}



