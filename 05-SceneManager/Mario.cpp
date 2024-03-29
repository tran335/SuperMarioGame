#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Questionbrick.h"
#include "Koopas.h"
#include "CameraBound.h"
#include "KoopasBound.h"
#include "BrickCoin.h"
#include "VenusFireTrap.h"
#include "FireBall.h"
#include "ParaGoomba.h"
#include "Parakoopa.h"
#include "Piranha.h"
#include "InOut.h"
#include "Pipe.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	LPGAME game = CGame::GetInstance();
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (isPickup == true) {
		if (!game->IsKeyDown(DIK_A)) {
			isPickup = false;
		}
	}
	if ((isDie) && (GetTickCount64() - die_start > MARIO_DIE_TIMEOUT))
	{
		isDie = false;
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
	}
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - spin_time > MARIO_SPIN_TIME && spin_time > 0)
	{
		spin_time = 0;
		isSpining = false;
	}
	if (isIn) {
		if (y >= startFront_y + 96)
		{
			if (isChangePosition) {
				vy = 0;
				SetPosition(6242, 1394);
				isChangePosition = false;
			}
			else {
				isFront = false;
				//vy = 0;
			}
			isIn = true;
		}
		else {
				vy = MARIO_FRONT_SPEED;
				isFront = true;
				y += vy * dt;
				vx = 0;
			}
	}
	else if (isOut) {
		if (y < startFront_y - 96)
		{
			front_start = 0;
			isFront = false;
			vy = 0;
			SetPosition(6917, 1054);
			isOut = false;
		}
		else
			vy = -MARIO_FRONT_SPEED;
			y += vy * dt;
	}
	else { isFront = false; }
	isOnPlatform = false;


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionbrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CCameraBound*>(e->obj))
		OnCollisionWithCameraBound(e);
	//else if (dynamic_cast<CKoopasBound*>(e->obj)) return;
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<CItems*>(e->obj))
		OnCollisionWithItems(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CParaKoopa*>(e->obj))
		OnCollisionWithParaKoopa(e);
	else if (dynamic_cast<CPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CInOut*>(e->obj))
		OnCollisionWithInOut(e);
	else if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			score += 100;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					if (isSpining)
					{
						if (goomba->GetState() != GOOMBA_STATE_KICK_BY_RACCOON)
						{
							goomba->SetState(GOOMBA_STATE_KICK_BY_RACCOON);
							isSpining = false;
							StartUntouchable();
						}
					}
					else {
						SetLevel(MARIO_LEVEL_BIG);
						StartUntouchable();
					}
				}
				else if ((level > MARIO_LEVEL_SMALL))
				{
					SetLevel(MARIO_LEVEL_SMALL);
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			
		}
	}

}

void CMario::OnCollisionWithInOut(LPCOLLISIONEVENT e)
{
	CInOut* inout = dynamic_cast<CInOut*>(e->obj);
	//DebugOut(L"Vo roi ne");
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		isIn = true;
		isOut = false;
		if (!isFront) startFront();
	}
	else if (e->ny > 0) {
		isOut = true;
		isIn = false;
		if (!isFront) startFront();
	}

}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	//DebugOut(L"Vo roi ne");
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		isChangePosition = true;
	}

}

void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* paragoomba = dynamic_cast<CParaGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (paragoomba->GetState() != PARAGOOMBA_STATE_DIE) {
			if (paragoomba->Getlevel() != PARAGOOMBA_LEVEL_NO_WING)
			{
				paragoomba->Setlevel(PARAGOOMBA_LEVEL_NO_WING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				score += 100;
				StartUntouchable();
			}
			else {
				paragoomba->SetState(PARAGOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				score += 100;
			}
		}

	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (paragoomba->GetState() != PARAGOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					if (isSpining)
					{
						if (paragoomba->GetState() != PARAGOOMBA_STATE_KICK_BY_RACCOON)
						{
							paragoomba->SetState(PARAGOOMBA_STATE_KICK_BY_RACCOON);
							isSpining = false;
							StartUntouchable();
						}
					}
					else {
						SetLevel(MARIO_LEVEL_BIG);
						StartUntouchable();
					}
				}
				else if ((level > MARIO_LEVEL_SMALL))
				{
					SetLevel(MARIO_LEVEL_SMALL);
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
					//CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithParaKoopa(LPCOLLISIONEVENT e)
{
	CParaKoopa* parakoopa = dynamic_cast<CParaKoopa*>(e->obj);
	LPGAME game = CGame::GetInstance();
	if (e->ny < 0)
	{
		if (parakoopa->GetState() != PARAKOOPA_STATE_DIE) {
			if (parakoopa->Getlevel() != PARAKOOPA_LEVEL_NO_WING)
			{
				//DebugOut(L"VO WALK ROI NE");
				parakoopa->Setlevel(PARAKOOPA_LEVEL_NO_WING);
				score += 100;
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			//	StartUntouchable();
			}
			else {
				//DebugOut(L"DIE LUN");
				parakoopa->SetState(PARAKOOPA_STATE_DIE);
				score += 100;
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (parakoopa->GetState() != PARAKOOPA_STATE_DIE)
			{
				CollisionEffect();
			}
			else {
				if (game->IsKeyDown(DIK_A) && (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))) {
					parakoopa->HandledByMario();
					isPickup = true;
				}
				else
				{
					SetState(MARIO_STATE_KICK);
					parakoopa->SetState(PARAKOOPA_STATE_SLIDE);
				}
				StartUntouchable();
			}
		}
	}
}


void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	LPGAME game = CGame::GetInstance();

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopas->GetState() != KOOPAS_STATE_DIE)
		{
			koopas->SetState(KOOPAS_STATE_DIE);
			score += 100;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					if (isSpining)
					{
							if (koopas->GetState() != KOOPAS_STATE_DIE && koopas->GetState() != KOOPAS_STATE_SLIDE)
							{
								koopas->SetState(KOOPAS_STATE_DIE);
							}
					}
					else {
						SetLevel(MARIO_LEVEL_BIG);
						StartUntouchable();
					}
				}
				else if ((level > MARIO_LEVEL_SMALL))
				{
					SetLevel(MARIO_LEVEL_SMALL);
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			else {
				if (game->IsKeyDown(DIK_A) && (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))) {
					koopas->HandledByMario();
					isPickup = true;
				}
				else {
					SetState(MARIO_STATE_KICK);
					koopas->SetState(KOOPAS_STATE_SLIDE);
				
				}
				StartUntouchable();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	score += 50;
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	if (e->ny < 0) {
		isOnPlatform = true;
	}
}

void CMario::OnCollisionWithCameraBound(LPCOLLISIONEVENT e)
{
	CCameraBound* camerabound = dynamic_cast<CCameraBound*>(e->obj);
	if (e->ny < 0) {
		SetState(MARIO_STATE_DIE);
	}
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
	if ((nx!=0 || ny!=0) && untouchable ==0)
	{
		CollisionEffect();
	}
}
void CMario::CollisionEffect()
{
	if (level > MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if ((level > MARIO_LEVEL_SMALL))
	{
		SetLevel(MARIO_LEVEL_SMALL);
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
		//CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
	}
}
void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	CVenusFireTrap* venus = dynamic_cast<CVenusFireTrap*>(e->obj);
	
	CollisionEffect();
}
void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);

	CollisionEffect();
}
void CMario::OnCollisionWithItems(LPCOLLISIONEVENT e)
{
	CItems* items = dynamic_cast<CItems*>(e->obj);
		if (level > MARIO_LEVEL_SMALL) {
			SetLevel(MARIO_LEVEL_RACCOON);
		}
		else {
			SetLevel(MARIO_LEVEL_BIG);
		}
		e->obj->Delete();
		score += 1000;
	
}
void CMario::OnCollisionWithKoopasBound(LPCOLLISIONEVENT e)
{
	CKoopasBound* koopasbound = dynamic_cast<CKoopasBound*>(e->obj);
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionbrick* questionbrick = dynamic_cast<CQuestionbrick*>(e->obj);
	if (e->ny > 0 && questionbrick->GetState()!=QUESTIONBRICK_STATE_DISABLE) {
		questionbrick->SetState(QUESTIONBRICK_STATE_DISABLE);
		if (questionbrick->GetItemType() == 1) {
			coin++;
			score += 100;
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}
void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT /2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isPickup)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_LEFT;
		}
		else
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (abs(vx) == MARIO_RUNNING_SPEED) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if(isPickup)
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_LEFT;
			}
			else if (vx > 0)
			{
					if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT;
			}
			else // vx < 0
			{
					if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT;
			}
		}
		else if (isKicking) {
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_MAX_RUN_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_MAX_RUN_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isPickup)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_PICK_UP_SHELL_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_PICK_UP_SHELL_LEFT;
		}
		else
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (abs(vx) == MARIO_RUNNING_SPEED) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isPickup)
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_PICK_UP_SHELL_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_PICK_UP_SHELL_LEFT;
			}
			else if (vx > 0)
			{
					if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_WALK_PICK_UP_SHELL_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALK_PICK_UP_SHELL_RIGHT;
			}
			else // vx < 0
			{
			 if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_WALK_PICK_UP_SHELL_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALK_PICK_UP_SHELL_LEFT;
			}
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_MAX_RUN_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_MAX_RUN_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isPickup)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_LEFT;
		}
		else if (isFront) {
			aniId = ID_ANI_MARIO_RACCOON_FRONT_PICK_UP_SHELL;
		}
		else 
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (abs(vx) != MARIO_RUNNING_SPEED) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_DROP_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_DROP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
				}
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
		}
		else if (isPickup)
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_LEFT;
			}
			else if (vx > 0)
			{
				 if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_RIGHT;
			}
			else // vx < 0
			{
				if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_LEFT;
			}
		}
		else if (isFront) {
			aniId = ID_ANI_MARIO_RACCOON_FRONT_PICK_UP_SHELL;
		}
		else if (vx == 0){
			if (isSpining) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_SPIN_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_SPIN_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
		}
		else if (vx > 0) {
			if (ax < 0)
				aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
			else if (abs(vx) == MARIO_RUNNING_SPEED)
				aniId = ID_ANI_MARIO_RACCOON_MAX_RUN_RIGHT;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
			else if (isSpining)
				aniId = ID_ANI_MARIO_RACCOON_SPIN_RIGHT;
			else /*if (ax == MARIO_ACCEL_WALK_X)*/
				aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
		else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (abs(vx) == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_MAX_RUN_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (isSpining)
					aniId = ID_ANI_MARIO_RACCOON_SPIN_LEFT;
				else /*if (ax == -MARIO_ACCEL_WALK_X)*/
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED && level > MARIO_LEVEL_BIG) {
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			}
			else 
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else {
			if (abs(this->vx) == MARIO_RUNNING_SPEED && level > MARIO_LEVEL_BIG)
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (abs(this->vx) == MARIO_RUNNING_SPEED && level > MARIO_LEVEL_BIG)
			vy += MARIO_JUMP_SPEED_Y / 4;
		else {
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		}
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_KICK:
		isKicking = true; 
		if (isKicking)
		{
			state = MARIO_STATE_IDLE;
		}
		break;


	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		isKicking = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DIE_SPEED;
		ax = 0.0f;
		vx = 0.0f;
		startDie();
	case MARIO_STATE_SPIN:
		isSpining = true;
		startSpin();
		break;
	case MARIO_STATE_SPIN_RELEASE:
		isSpining = false;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::SetLevel(int l)
{
	level = l;
	switch (l)
	{
	case MARIO_LEVEL_SMALL:
		this->y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;			
		break;
	case MARIO_LEVEL_BIG:
		this->y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
		break;
	case MARIO_LEVEL_RACCOON:
		this->y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT;
		break;
	}
	
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();


	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	DebugOutTitle(L"SCORE: %d", score);
}