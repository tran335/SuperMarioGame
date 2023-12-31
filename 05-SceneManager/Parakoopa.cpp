#include "Parakoopa.h"
#include "PlayScene.h"
#include "Questionbrick.h"
#include "Platform.h"
#include "Bigbox.h"
CParaKoopa::CParaKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAKOOPA_GRAVITY;
	this->type = type;
	start_y = y;
	start_x = x;
	maxVx = PARAKOOPA_WALKING_SPEED;
	maxVy = PARAKOOPA_WALKING_SPEED_MAX;
	die_start = -1;
	waking_start = -1;
	reset_time = -1;
	/*untouchable = 0;
	untouchable_start = -1;*/
	isOnPlatform = false;
	nx = -1;
	level = PARAKOOPA_LEVEL_WING;
	SetState(PARAKOOPA_STATE_FLY);
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}
LPGAME game1 = CGame::GetInstance();
void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAKOOPA_STATE_DIE || state == PARAKOOPA_STATE_SLIDE)
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT;
	}
}

void CParaKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaKoopa*>(e->obj)) return;

	if (e->ny < 0)
	{
		vy = 0;
		isOnPlatform = true;

	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CQuestionbrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	if (dynamic_cast<CCameraBound*>(e->obj))
		OnCollisionWithCameraBound(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CBigbox*>(e->obj))
		OnCollisionWithBigBox(e);

}
void CParaKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionbrick* questionbrick = dynamic_cast<CQuestionbrick*>(e->obj);
	if (this->state == PARAKOOPA_STATE_SLIDE) {
		if (questionbrick->GetState() != QUESTIONBRICK_STATE_DISABLE)
		{
			questionbrick->SetState(QUESTIONBRICK_STATE_DISABLE);
			vx = -vx;
		}
	}
}

void CParaKoopa::OnCollisionWithCameraBound(LPCOLLISIONEVENT e)
{
	CCameraBound* camerabound = dynamic_cast<CCameraBound*>(e->obj);
	if ((e->ny < 0) && isBack == false)
	{
		startBack();
	}
}

void CParaKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	/*if (e->ny < 0)
	{
		if (level == PARAKOOPA_LEVEL_WING && isOnPlatform == true) {
			if (untouchable == 0) {
				vy = -PARAKOOPA_JUMP_Y;
			}
		}
		else if (state == PARAKOOPA_STATE_DIE) {
			SetState(PARAKOOPA_STATE_DIE);
		}
	}*/
}

void CParaKoopa::OnCollisionWithBigBox(LPCOLLISIONEVENT e)
{
	CBigbox* bigbox = dynamic_cast<CBigbox*>(e->obj);
	if (e->ny < 0)
	{
		if (level == PARAKOOPA_LEVEL_WING && isOnPlatform == true) {
				vy = -PARAKOOPA_JUMP_Y;
		}
	}
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	isOnPlatform = false;
	if (state == PARAKOOPA_STATE_FLY || state == PARAKOOPA_STATE_WALKING) {
		if (abs(vx) > abs(maxVx)) {
			if (vx > 0) vx = maxVx;
			else vx = -maxVx;
		}
		if (abs(vy) > abs(maxVy)) {
			if (vy > 0) vy = maxVy;
			else vy = -maxVy;
		}
	}

	if (isHandled == true) {
		if (game1->IsKeyDown(DIK_A)) {
			setPositionHandled();
		}
		else {
			HandledByMarioRelease();
			SetState(PARAKOOPA_STATE_SLIDE);
		}
	}
	//if (level == PARAKOOPA_LEVEL_WING) {
	//	SetState(PARAKOOPA_STATE_FLY);
	//}

	if ((state == PARAKOOPA_STATE_DIE) && (GetTickCount64() - die_start > PARAKOOPA_DIE_TIMEOUT))
	{
		SetState(PARAKOOPA_STATE_WAKING);
		startWakingTime();
	}
	else if (state == PARAKOOPA_STATE_WAKING && (GetTickCount64() - waking_start > PARAKOOPA_WAKING_TIMEOUT)) {
		SetState(PARAKOOPA_STATE_FLY);
		waking_start = 0;
	}
	if (isBack == true && (GetTickCount64() - reset_time > BACK_TIME) && state != PARAKOOPA_STATE_SLIDE) {
		SetPosition(start_x, start_y);
		isBack = false;
		reset_time = 0;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaKoopa::Render()
{

	int aniId = -1;


	if (level == PARAKOOPA_LEVEL_WING) {
		if (vx > 0)
			aniId = ID_ANI_PARAKOOPA_FLY_RIGHT;
		else
			aniId = ID_ANI_PARAKOOPA_FLY_LEFT;
	}
	else {
		if (state == PARAKOOPA_STATE_DIE)
			aniId = ID_ANI_PARAKOOPA_DIE;
		else if (state == PARAKOOPA_STATE_SLIDE)
			aniId = ID_ANI_PARAKOOPA_SLIDE;
		else if (state == PARAKOOPA_STATE_WAKING)
			aniId = ID_ANI_PARAKOOPA_WAKING;
		else {
			if (vx > 0)
				aniId = ID_ANI_PARAKOOPA_WALKING_RIGHT;
			else
				aniId = ID_ANI_PARAKOOPA_WALKING_LEFT;
		}

	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAKOOPA_STATE_FLY:
		DebugOut(L"FLY");
		//vx = -PARAKOOPA_WALKING_SPEED;
		ax = -PARAKOOPA_GRAVITY_X;
		ay = PARAKOOPA_GRAVITY;
		break;
	case PARAKOOPA_STATE_DIE:
		DebugOut(L"DIE");
		die_start = GetTickCount64();
		y += (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = PARAKOOPA_GRAVITY;
		break;
	//case PARAKOOPA_STATE_WALKING:
	//	DebugOut(L"WALKING");
	//	if (waking_start > 0) {
	//		y -= (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
	//	}
	//	vx = -PARAKOOPA_WALKING_SPEED;
	//	ay = PARAKOOPA_GRAVITY;
	//	break;
	case PARAKOOPA_STATE_SLIDE:
		DebugOut(L"SLIDE");
		ay = PARAKOOPA_GRAVITY;
		setPositionSlide();
		break;
	case PARAKOOPA_STATE_WAKING:
		DebugOut(L"WAKING");
		if (isOnPlatform) {
			y -= (PARAKOOPA_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		}
		break;
	}
}
void CParaKoopa::setPositionSlide()
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x < x_mario)
		vx = -PARAKOOPA_SLIDE_SPEED;
	else
		vx = PARAKOOPA_SLIDE_SPEED;
}
void CParaKoopa::setPositionHandled()
{
	float x_mario, y_mario, nx_mario, ny_mario;
	mario->GetPosition(x_mario, y_mario);
	mario->GetDirection(nx_mario, ny_mario);

	if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
		if (nx_mario < 0)
			SetPosition(x_mario - MARIO_SMALL_HANDLED_WIDTH, y_mario - MARIO_SMALL_HANDLED_HEIGHT);
		else if (nx_mario > 0)
			SetPosition(x_mario + MARIO_SMALL_HANDLED_WIDTH, y_mario - MARIO_SMALL_HANDLED_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_BIG) {
		if (nx_mario < 0)
			SetPosition(x_mario - MARIO_BIG_HANDLED_WIDTH, y_mario + MARIO_BIG_HANDLED_HEIGHT);
		else if (nx_mario > 0)
			SetPosition(x_mario + MARIO_BIG_HANDLED_WIDTH, y_mario + MARIO_BIG_HANDLED_HEIGHT);
	}
	else {
		if (nx_mario < 0)
			SetPosition(x_mario - MARIO_RACCOON_HANDLED_WIDTH, y_mario + MARIO_RACCOON_HANDLED_HEIGHT);
		else if (nx_mario > 0)
			SetPosition(x_mario + MARIO_RACCOON_HANDLED_WIDTH, y_mario + MARIO_RACCOON_HANDLED_HEIGHT);
	}
}
