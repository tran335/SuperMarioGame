#include "Questionbrick.h"
#include "PlayScene.h"
#include "BrickCoin.h"
#include "Items.h"


CMario* mario = NULL;
CQuestionbrick::CQuestionbrick(float x, float y, int item_type)
{
	this->x = x;
	this->y = y;
	start_y = y;
	this->item_type = item_type;
	hasItem = true;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CQuestionbrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float mario_vx, mario_vy;
	mario->GetSpeed(mario_vx, mario_vy);

	if (GetState() == QUESTIONBRICK_STATE_DISABLE ) {
		isThrow = 1;
		if (throwup_start == 0) {
			StartThrowup();
		}
		else if (GetTickCount64() - throwup_start > 0) {
			if (y < start_y)
				y++;
			else
				y = start_y;
		}
	}
	else
		isThrow = 0;
	
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
void CQuestionbrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTIONBRICK_STATE_DISABLE:
		vx = 0;
		vy = 0;
		y = y - QUESTIONBRICK_JUMP_Y;
		if (hasItem == true) {
			CItems* items = new CItems(x, y);
			if (item_type == 2) {

				if (mario->GetLevel() > MARIO_LEVEL_SMALL) {
					items->SetState(ITEMS_STATE_LEAF);
					CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
					scene->objects.push_back(items);
				}
				else {
					/*if (mario_vx < 0) {
						items->SetState(ITEMS_STATE_SUPERMUSHROOM);
					}
					else {*/
						items->SetState(ITEMS_STATE_SUPERMUSHROOM_RIGHT);
					//}
					CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
					scene->objects.push_back(items);
				}
			}
			else {
				CBrickCoin* brickcoin = new CBrickCoin(x, y);
				CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
				scene->objects.push_back(brickcoin);
				brickcoin->SetState(BRICKCOIN_STATE_THROW_UP);
			}
			hasItem = false;
		}
		break;
	}
}