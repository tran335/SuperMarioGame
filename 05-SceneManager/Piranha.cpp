#include "Piranha.h"
#include "PlayScene.h"


CPiranha::CPiranha(float x, float y)
{
	this->x = x;
	this->y = y;
	start_y = y;
	start_time = 0;
	vy = -PIRANHA_SPEED;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;
	/*if (start_time == 0) {
		if (y < start_y - PIRANHA_HEIGHT) {
			vy = 0.0f;
			startTime();
		}
	}

	else if (GetTickCount64() - start_time > GROW_UP_TIME && start_time > 0) {
		start_time = 0;
		vy = PIRANHA_SPEED;
	}
	if (y >= start_y + PIRANHA_HEIGHT_DOWN) {
		vy = -PIRANHA_SPEED;
	}*/
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);

	if (((x - x_mario < PIRANHA_WIDTH) && (((x + PIRANHA_WIDTH) - x_mario) > 0)) || ((y - y_mario > 0) && (((x + PIRANHA_WIDTH) - x_mario) > 0) && (x - x_mario < 0))) {
		isStop = true;
	}
	else {
		isStop = false;
	}
	if (start_time == 0) {
		if (y < start_y - PIRANHA_HEIGHT) {
			vy = 0.0f;
			startTime();
		}
	}

	else if (GetTickCount64() - start_time > GROW_UP_TIME && start_time > 0) {
		start_time = 0;
		vy = PIRANHA_SPEED;
	}
	if (y >= start_y + PIRANHA_HEIGHT_DOWN) {
		if (isStop == true) {
			vy = 0;
		}
		else
		vy = -PIRANHA_SPEED;
	}
	CGameObject::Update(dt, coObjects);

}

void CPiranha::Render()
{
	int aniId = IC_ANI_PIRANHA;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}



void CPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_BBOX_WIDTH / 2;
	t = y - PIRANHA_BBOX_HEIGHT / 2;
	r = l + PIRANHA_BBOX_WIDTH;
	b = t + PIRANHA_BBOX_HEIGHT;
}


