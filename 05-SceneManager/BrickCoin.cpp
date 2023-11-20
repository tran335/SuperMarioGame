#include "BrickCoin.h"

CBrickCoin::CBrickCoin(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CBrickCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICKCOIN)->Render(x, y);
}

void CBrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

