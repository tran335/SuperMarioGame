#include "ReverseObject.h"

void CReverseObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
		if (!e->obj->IsBlocking()) return;

}

CReverseObject::CReverseObject(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CReverseObject::Render()
{
	RenderBoundingBox();
}

void CReverseObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
