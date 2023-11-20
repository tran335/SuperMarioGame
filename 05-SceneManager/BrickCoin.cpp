#include "BrickCoin.h"
#include "PlayScene.h"


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

void CBrickCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICKCOIN_BBOX_WIDTH / 2;
	top = y - BRICKCOIN_BBOX_HEIGHT / 2;
	right = left + BRICKCOIN_BBOX_WIDTH;
	bottom = top + BRICKCOIN_BBOX_HEIGHT;
};

void CBrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICKCOIN_STATE_THROWUP:
		OutputDebugString(L"Vo rui ne");
		vx = 0;
		vy = 0;
		y = y - 10.0f;
		break;
	}
}

