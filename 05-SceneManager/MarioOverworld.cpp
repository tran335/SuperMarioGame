#include <algorithm>
#include "debug.h"

#include "MarioOverworld.h"
#include "Game.h"

#include "Platform.h"
#include "Tree.h"
#include "Portal.h"

#include "Collision.h"

void CMarioOverworld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if (abs(vx) > abs(maxVx)) vx = maxVx;
	//if (abs(vy) > abs(maxVy)) vy = maxVy;

	LPGAME game = CGame::GetInstance();
	if (isWitchscene == true && game->IsKeyDown(DIK_S)) {
		CGame::GetInstance()->InitiateSwitchScene(3);
		isWitchscene = false;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);



}

void CMarioOverworld::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

}

void CMarioOverworld::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0) {
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
	}
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
}

void CMarioOverworld::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (e->ny != 0) {
		vy = 0;
		ay = 0;

	}
}


void CMarioOverworld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MARIO;

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

}

void CMarioOverworld::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		x = x + 96;
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_WALKING_LEFT:
		x = x - 96;
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_WALKING_UP:
		y = y - 96;
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_WALKING_DOWN:
		y = y + 96;
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		vy = 0.0f;
		break;
	}


	CGameObject::SetState(state);
}

void CMarioOverworld::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_SMALL_BBOX_WIDTH / 2;
	top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
	right = left + MARIO_SMALL_BBOX_WIDTH;
	bottom = top + MARIO_SMALL_BBOX_HEIGHT;

}
