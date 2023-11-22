#include "Items.h"

CItems::CItems(float x, float y)
{
	this->x = x;
	this->y = y;
	ax = -SUPERMUSHROOM_GRAVITY;
	ay = -SUPERMUSHROOM_GRAVITY;
	start_y = y;
}

void CItems::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_SUPERMUSHROOM;
	animations->Get(aniId)->Render(x, y);
}


void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isCollidable = true;
	vy += ay * dt;
	x += vx * dt;

	if (y < start_y - ITEMS_BBOX_HEIGHT) {
		vy = 0.0f;
		ay = -ay;
		vx = -SUPERMUSHROOM_WALKING_SPEED;
		y = start_y - ITEMS_BBOX_HEIGHT;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CItems::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ITEMS_BBOX_WIDTH / 2;
	top = y - ITEMS_BBOX_HEIGHT / 2;
	right = left + ITEMS_BBOX_WIDTH;
	bottom = top + ITEMS_BBOX_HEIGHT;
}

void CItems::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CItems::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CItems*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CQuestionbrick*>(e->obj))
		OnCollisionWithQuestionbrick(e);
}

void CItems::OnCollisionWithQuestionbrick(LPCOLLISIONEVENT e)
{
	CQuestionbrick* questionbrick = dynamic_cast<CQuestionbrick*>(e->obj);
	if (e->ny < 0 ) {
		isCollidable = false;
	}
	else
		isCollidable = true;
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEMS_STATE_SUPERMUSHROOM:
		//vy = -ITEMS_BBOX_HEIGHT;
		//vx = -SUPERMUSHROOM_WALKING_SPEED;
		vx = 0;
		break;
	}
}
