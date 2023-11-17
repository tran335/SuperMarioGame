#include "Questionbrick.h"

CQuestionbrick::CQuestionbrick(float x, float y, int item_type)
{
	this->x = x;
	this->y = y;
	start_y = y;
	this->item_type = item_type;

}

void CQuestionbrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	
}


void CQuestionbrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_QUESTIONBRICK_NORMAL;
	if (state == QUESTIONBRICK_STATE_DISABLE) {
		aniId = ID_ANI_QUESTIONBRICK_DISABLE;
	}
	animations->Get(aniId)->Render(x, y);
}

void CQuestionbrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESTIONBRICK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = t + QUESTIONBRICK_BBOX_HEIGHT;
}
