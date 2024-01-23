#include "Three.h"

void CThree::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_THREE)->Render(x, y);

	//RenderBoundingBox();
}

void CThree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - THREE_BBOX_WIDTH / 2;
	t = y - THREE_BBOX_HEIGHT / 2;
	r = l + THREE_BBOX_WIDTH;
	b = t + THREE_BBOX_HEIGHT;
}
