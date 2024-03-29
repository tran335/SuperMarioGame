#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "BrickCoin.h"
#include "Items.h"
#include "Platform.h"


#define MARIO_WALKING_SPEED		0.3f
#define MARIO_RUNNING_SPEED		0.7f

#define MARIO_FRONT_SPEED		0.1f

#define MARIO_MAX_VX 0.7f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		1.0f
#define MARIO_JUMP_RUN_SPEED_Y	1.5f
#define MARIO_JUMP_RELEASE_FLY_SPEED_Y		0.5f
#define MARIO_JUMP_DIE_SPEED 1.0f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK			700

#define MARIO_STATE_SPIN	800
#define MARIO_STATE_SPIN_RELEASE 801

#pragma region ANIMATION_ID
//BIG MARIO
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 1101
#define ID_ANI_MARIO_KICK_LEFT 1110

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_IDLE_PICK_UP_SHELL_LEFT 12000
#define ID_ANI_MARIO_IDLE_PICK_UP_SHELL_RIGHT 12010

#define ID_ANI_MARIO_WALK_PICK_UP_SHELL_LEFT 13000
#define ID_ANI_MARIO_WALK_PICK_UP_SHELL_RIGHT 13010

#define ID_ANI_MARIO_JUMP_PICK_UP_SHELL_LEFT 14000
#define ID_ANI_MARIO_JUMP_PICK_UP_SHELL_RIGHT 14010

#define ID_ANI_MARIO_FRONT_PICK_UP_SHELL 15000

#define ID_ANI_MARIO_MAX_RUN_RIGHT 16000
#define ID_ANI_MARIO_MAX_RUN_LEFT 16010

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1701
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1700

#define ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_LEFT 18000
#define ID_ANI_MARIO_SMALL_IDLE_PICK_UP_SHELL_RIGHT 18010

#define ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_LEFT 19000
#define ID_ANI_MARIO_SMALL_WALK_PICK_UP_SHELL_RIGHT 19010

#define ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_LEFT 20000
#define ID_ANI_MARIO_SMALL_JUMP_PICK_UP_SHELL_RIGHT 20010

#define ID_ANI_MARIO_SMALL_FRONT_PICK_UP_SHELL 21000

#define ID_ANI_MARIO_SMALL_MAX_RUN_RIGHT 22000
#define ID_ANI_MARIO_SMALL_MAX_RUN_LEFT 22010

//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1160
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 160

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1161
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 161

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 1162
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 162

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1164
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 164

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 1163
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 163

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 1167
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 167

#define  ID_ANI_MARIO_RACCOON_MAX_RUN_RIGHT 1166
#define ID_ANI_MARIO_RACCOON_MAX_RUN_LEFT 166

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 1170
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 170

#define ID_ANI_MARIO_RACCOON_DROP_RIGHT 1165
#define ID_ANI_MARIO_RACCOON_DROP_LEFT 165

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 1168
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 168

#define ID_ANI_MARIO_RACCOON_SPIN_RIGHT 1169
#define ID_ANI_MARIO_RACCOON_SPIN_LEFT 169

#define ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_LEFT 1710
#define ID_ANI_MARIO_RACCOON_IDLE_PICK_UP_SHELL_RIGHT 11710

#define ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_LEFT 1720
#define ID_ANI_MARIO_RACCOON_WALK_PICK_UP_SHELL_RIGHT 11720

#define ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_LEFT 1730
#define ID_ANI_MARIO_RACCOON_JUMP_PICK_UP_SHELL_RIGHT 11730

#define ID_ANI_MARIO_RACCOON_FRONT_PICK_UP_SHELL 1740



#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3

#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 80
#define MARIO_BIG_SITTING_BBOX_WIDTH  43
#define MARIO_BIG_SITTING_BBOX_HEIGHT 49

#define MARIO_RACCOON_BBOX_WIDTH  65
#define MARIO_RACCOON_BBOX_HEIGHT 82
#define MARIO_RACCOON_SITTING_BBOX_WIDTH  63
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 52

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 42

#define MARIO_SPIN_TIME 1000
#define MARIO_UNTOUCHABLE_TIME 2500
#define  MARIO_DIE_TIMEOUT 1000
#define  MARIO_FRONT_TIMEOUT 700

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isKicking;
	BOOLEAN isSpining;
	BOOLEAN isChangePosition;
	BOOLEAN isFront;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	float startFront_y;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG spin_time;
	ULONGLONG die_start;
	ULONGLONG front_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isDie;
	BOOLEAN isIn;
	BOOLEAN isOut;
	bool isPickup;
	int coin; 
	int score;
	

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithCameraBound(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopasBound(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithItems(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithInOut(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void CollisionEffect();
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y) : CGameObject(x, y) 
	{
		isSitting = false;
		isKicking = false;
		isSpining = false;
		isChangePosition = false;
		isIn = false;
		isOut = false;
		isDie = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		spin_time = -1;
		die_start = -1;
		isOnPlatform = false;
		isFront = false;
		isPickup = false;
		coin = 0;
		score = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	bool IsPickup() { return isPickup; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void startSpin() { spin_time = GetTickCount64(); }
	void startDie() { isDie = true; die_start = GetTickCount64(); }
	void startFront() { startFront_y = y; isFront = true; }
	int GetCoin() { return coin; }
	int GetScore() { return score; }

};