#include <algorithm>
#include "debug.h"

#include "MarioOverworld.h"
#include "Game.h"

#include "Platform.h"
#include "Tree.h"
#include "Portal.h"

#include "Collision.h"
#include "PlayScene.h"

void CMarioOverworld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	LPGAME game = CGame::GetInstance();
	if (isWitchscene == true && game->IsKeyDown(DIK_S)) {
		CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_1_1_SCENE);
		isWitchscene = false;
	}
	if (isWalkingY && abs(y - start_y) >= MARIO_DISTANCE_Y) {
		SetState(MARIO_STATE_IDLE);
		start_y = y;
		//DebugOut(L"vy =0");
	}
	if (isWalkingX && abs(x - start_x) >= MARIO_DISTANCE_X) {
		//DebugOut(L"vx =0");
		SetState(MARIO_STATE_IDLE);
		start_x = x;
	}
	if (state == MARIO_STATE_IDLE) {
		startCheckNode();
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
		//x = x + 96;
		//vx = 0;
		isWalkingX = true;
		isWalkingY = false;
		ax = MARIO_GRAVITY;
		break;
	case MARIO_STATE_WALKING_LEFT:
		//x = x - 96;
		//vx = 0;
		isWalkingX = true;
		isWalkingY = false;
		ax = -MARIO_GRAVITY;
		break;
	case MARIO_STATE_WALKING_UP:
		//y = y - 96;
		isWalkingY = true;
		isWalkingX = false;
		ay = -MARIO_GRAVITY;
		break;
	case MARIO_STATE_WALKING_DOWN:
		//y = y + 96;
		isWalkingY = true;
		isWalkingX = false;
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_IDLE:
		isWalkingX = false;
		isWalkingY = false;
		ax = 0.0f;
		ay = 0.0f;
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

void CMarioOverworld::startCheckNode()
{	
	if ((x >= NODE_1_X && x <=(NODE_1_X + NODE_WIDTH)) && (y >= NODE_1_Y && y <= (NODE_1_Y + NODE_HEIGHT))
		|| (x >= NODE_2_X && x <= (NODE_2_X + NODE_WIDTH)) && (y >= NODE_2_Y && y <= (NODE_2_Y + NODE_HEIGHT))
		|| (x >= NODE_3_X && x <= (NODE_3_X + NODE_WIDTH)) && (y >= NODE_3_Y && y <= (NODE_3_Y + NODE_HEIGHT))
		|| (x >= NODE_4_X && x <= (NODE_4_X + NODE_WIDTH)) && (y >= NODE_4_Y && y <= (NODE_4_Y + NODE_HEIGHT))
		|| (x >= NODE_5_X && x <= (NODE_5_X + NODE_WIDTH)) && (y >= NODE_5_Y && y <= (NODE_5_Y + NODE_HEIGHT))
		|| (x >= NODE_6_X && x <= (NODE_6_X + NODE_WIDTH)) && (y >= NODE_6_Y && y <= (NODE_6_Y + NODE_HEIGHT))) 
	{
		isWitchscene = true; DebugOut(L"vo duoc day roi");
	}
	else isWitchscene = false;
}
