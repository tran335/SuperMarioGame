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
		SetState(BRICKCOIN_STATE_DROP);
	}
	if (state == BRICKCOIN_STATE_DROP && y > start_y - BRICKCOIN_MIN_Y) {
		vy = 0;
		this->Delete();
	}

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
	case BRICKCOIN_STATE_DROP:
		vy = BRICKCOIN_JUMP_SPEED_Y;
		break;
	}
}



