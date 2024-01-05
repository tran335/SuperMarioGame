#include "Tree.h"

void CTree::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREE)->Render(x, y);
	RenderBoundingBox();
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}