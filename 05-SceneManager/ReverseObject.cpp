#include "ReverseObject.h"


CReverseObject::CReverseObject(float x, float y)
{
	this->x = x;
	this->y = y;
}
void CReverseObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CItems*>(e->obj)) return;
	if (dynamic_cast<CReverseObject*>(e->obj)) return;
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);

}
void CReverseObject::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj); 
	if (e->nx != 0 || e->ny !=0) {
		DebugOut(L"ZOO");
	}
}
void CReverseObject::Render()
{
	//RenderBoundingBox();
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
