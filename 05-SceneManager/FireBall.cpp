#include "FireBall.h"
#include "PlayScene.h"
#include "BigBox.h"
#include "Platform.h"



void CFireBall::OnNoCollision(DWORD dt)
{
	if (nx < 0) {
		x += -vx*dt;
		if (ny < 0)
			y += vy * dt;
		else
			y -= vy * dt;
	}
	if (nx > 0) {
		x += vx * dt;
		if (ny < 0)
			y -= vy * dt;
		else
			y += vy * dt;
	}

}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

}

CFireBall::CFireBall(float x, float y)
{
	this->x = x;
	this->y = y- FIREBALL_Y;
	//ax = 0;
	unfindslidedirecttion_time = -1;
	unfindslidedirecttion = 1;
	//ay = FIREBALL_GRAVITY;
	//ax = FIREBALL_GRAVITY;
	vx = FIRE_BALL_SPEED_X;
	vy = FIRE_BALL_SPEED_Y;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CFireBall::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ID_ANI_FIREBALL;
	animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}


void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (unfindslidedirecttion) {
		startfindslidedirecttion(dt);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::startfindslidedirecttion(DWORD dt)
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);

	if (x_mario < x) {
		nx = -1;
		if (y_mario > y) {
			ny = -1;
		}
		else if (y_mario < y) {
			ny = 1;
		}
	}

	else if (x_mario > x) {
		nx = 1;
		if (y_mario > y) {
			ny = 1;
		}
		else if (y_mario < y) {
			ny = -1;
		}
	}
	unfindslidedirecttion = 0;
}

