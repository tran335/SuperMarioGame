#include "VenusFireTrap.h"
#include "PlayScene.h"

CVenusFireTrap::CVenusFireTrap(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	start_y = y;
	vy = -VENUS_SPEED;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

}

void CVenusFireTrap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	if (isRight == true) {
		if (isShooting == true) {
			if (isUp == true)
				aniId = ID_ANI_VENUS_SHOOT_UP_RIGHT;
			else
				aniId = ID_ANI_VENUS_SHOOT_DOWN_RIGHT;
		}
		else
			if (isUp == true) {
				aniId = ID_ANI_VENUS_UP_RIGHT;
			}
			else
				aniId = IC_ANI_VENUS_DOWN_RIGHT;
	}
	else
	{
		if (isShooting == true) {
			if (isUp == true)
				aniId = ID_ANI_VENUS_SHOOT_UP_LEFT;
			else
				aniId = ID_ANI_VENUS_SHOOT_DOWN_LEFT;
		}
		else
			if (isUp == true) {
				aniId = ID_ANI_VENUS_UP_LEFT;
			}
			else
				aniId = IC_ANI_VENUS_DOWN_LEFT;
	}
	animations->Get(aniId)->Render(x, y);
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += vy;
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (((x - x_mario < VENUS_WIDTH) && (((x + VENUS_WIDTH) - x_mario) > 0)) || ((y - y_mario > 0) && (((x + VENUS_WIDTH) - x_mario) > 0) && (x - x_mario < 0))) {
		isStop = true;
	}
	else {
		isStop = false;
	}
	if (isShooting == false) {
		if (y_mario > y)
			isUp = false;
		else if (y_mario < y)
			isUp = true;
		if (x_mario < x) {
			isRight = false;
		}
		else if (x_mario > x) {
			isRight = true;
		}
		if (y < start_y - VENUS_HEIGHT) // have not overlap with pipe
		{
			vy = 0.0f;
			startShootingTime();
			CFireBall* fireball = new CFireBall(x, y);
			CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			scene->objects.push_back(fireball);
		
		}
	}
	else if (GetTickCount64() - shootingTime > VENUS_SHOOTING_TIME) {

		shootingTime = 0;
		isShooting = false;
		vy = VENUS_SPEED;
	}
	if (y > start_y + VENUS_HEIGHT) {
		if (isStop == true) {
			vy = 0;
		}
		else
			vy = -VENUS_SPEED;
	}
	
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_BBOX_WIDTH / 2;
	t = y - VENUS_BBOX_HEIGHT / 2;
	r = l + VENUS_BBOX_WIDTH;
	b = t + VENUS_BBOX_HEIGHT;
}

void CVenusFireTrap::startShootingTime()
{
	isShooting = true;
	shootingTime = GetTickCount64(); 
}
