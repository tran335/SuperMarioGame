#include "ReverseObject.h"


CReverseObject::CReverseObject(float x, float y)
{
	this->x = x;
	this->y = y;
	isFall = 0;
}
void CReverseObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CReverseObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
	}
}

void CReverseObject::Render()
{
	//RenderBoundingBox();
}

void CReverseObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	isFall = 0;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CReverseObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - REVERSEOBJECT_BBOX_WIDTH / 2;
	t = y - REVERSEOBJECT_BBOX_HEIGHT / 2;
	r = l + REVERSEOBJECT_BBOX_WIDTH;
	b = t + REVERSEOBJECT_BBOX_HEIGHT;
}
