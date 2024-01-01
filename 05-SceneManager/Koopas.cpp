#include "Koopas.h"
#include "PlayScene.h"

LPGAME game = CGame::GetInstance();
CReverseObject* reverseobject = NULL;
CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	isOnPlatform = false;
	SetState(KOOPAS_STATE_WALKING);
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_SLIDE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else if (state == KOOPAS_STATE_WAKING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_WAKE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_WAKE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CItems*>(e->obj)) return;
	if (dynamic_cast<CReverseObject*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CQuestionbrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCameraBound*>(e->obj))
		OnCollisionWithCameraBound(e);

}
void CKoopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionbrick* questionbrick = dynamic_cast<CQuestionbrick*>(e->obj);
	if (this->state == KOOPAS_STATE_SLIDE) {
		if (questionbrick->GetState() != QUESTIONBRICK_STATE_DISABLE)
		{
			questionbrick->SetState(QUESTIONBRICK_STATE_DISABLE);
			vx = -vx;
		}
	}

}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (this->state == KOOPAS_STATE_SLIDE) {
		goomba->SetState(GOOMBA_STATE_KICK_BY_KOOPAS);
	}
	DebugOut(L"Vo day roi ne");
}

void CKoopas::OnCollisionWithCameraBound(LPCOLLISIONEVENT e)
{
	isDrop = true;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	isOnPlatform = false;
//	isDrop = false;
	if (isHandled == true) {
		if (game->IsKeyDown(DIK_A)) {
			setPositionByHandle();
		}
		else {
			HandledByMarioRelease();
			if (state == KOOPAS_STATE_DIE) {
				SetState(KOOPAS_STATE_SLIDE);
			}
		}
	}

	if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT) /*&& isHandled != true*/)
	{
		SetState(KOOPAS_STATE_WAKING);
		startWakingTime();
	}
	else if (state == KOOPAS_STATE_WAKING && (GetTickCount64() - waking_start > KOOPAS_WAKING_TIMEOUT)) {
		SetState(KOOPAS_STATE_WALKING);
		waking_start = 0;
	}
	CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (reverseobject == NULL) {
		reverseobject = new CReverseObject(x, y);
		scene->objects.push_back(reverseobject);
	}
	else {
		if (vx > 0)
		{
			reverseobject->SetPosition(x + 58, y);
		}
		else
		{
			reverseobject->SetPosition(x - 58, y);
		}
	}
	
	
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = 0;
	if (state == KOOPAS_STATE_WALKING) {
		if (vx > 0)
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		else
			aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_SLIDE) {
		aniId = ID_ANI_KOOPAS_SLIDE;
	}
	else if (state == KOOPAS_STATE_DIE)
	{
		aniId = ID_ANI_KOOPAS_DIE;
	}
	if (state == KOOPAS_STATE_WAKING) {
		aniId = ID_ANI_KOOPAS_WAKING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		if (isHandled == true) {
			ay = KOOPAS_GRAVITY;
		}
		else {
			ay = 0;
		}
		break;
	case KOOPAS_STATE_WALKING:
		if (waking_start > 0) {
			y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		}
		vx = -KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_SLIDE:
		ay = KOOPAS_GRAVITY;
		setPositionSlide();
		break;
	case KOOPAS_STATE_WAKING:
		if (isOnPlatform) {
			y -= (KOOPAS_BBOX_HEIGHT_WAKE - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		}
		//ay = KOOPAS_GRAVITY;
		break;

	}
}
void CKoopas::setPositionSlide()
{
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x < x_mario)
		vx = -KOOPAS_SLIDE_SPEED;
	else
		vx = KOOPAS_SLIDE_SPEED;
}

void CKoopas::HandledByMario()
{
	isHandled = true;
}

void CKoopas::HandledByMarioRelease()
{
	isHandled = false;
}

void CKoopas::setPositionByHandle()
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
