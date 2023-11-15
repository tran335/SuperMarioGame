#include "Bigbox.h"



void CBigbox::RenderBoundingBox()
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

	float xx = x - BIGBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - BIGBOX_HEIGHT / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

int CBigbox::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
CBigbox::CBigbox(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CBigbox::Render()
{
	//RenderBoundingBox();
}

void CBigbox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BIGBOX_WIDTH / 2;
	t = y - BIGBOX_HEIGHT / 2;
	r = l + width;
	b = t + height;
}
