#include "KoopasBound.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CKoopasBound::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - KOOPASBOUND_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - KOOPASBOUND_BBOX_HEIGHT / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

CKoopasBound::CKoopasBound(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CKoopasBound::Render()
{
	//RenderBoundingBox();
}

void CKoopasBound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - KOOPASBOUND_BBOX_WIDTH / 2;
	t = y - KOOPASBOUND_BBOX_HEIGHT / 2;
	r = l + width;
	b = t + height;
}
