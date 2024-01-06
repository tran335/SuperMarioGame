#include "InOut.h"



void CInOut::RenderBoundingBox()
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

	float xx = x - INOUT_WIDTH / 2 + rect.right / 2;
	float yy = y - INOUT_HEIGHT / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

int CInOut::IsDirectionColliable(float nx, float ny)
{
	return 1;
}
CInOut::CInOut(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CInOut::Render()
{
	//RenderBoundingBox();
}

void CInOut::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - INOUT_WIDTH / 2;
	t = y - INOUT_HEIGHT / 2;
	r = l + width;
	b = t + height;
}
