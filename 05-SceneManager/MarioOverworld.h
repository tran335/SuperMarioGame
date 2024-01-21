#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Mario.h"

#include "Node.h"
#include "PlayScene.h"

#define MARIO_WALKING_SPEED		0.3f

#define MARIO_GRAVITY			0.0015f

#define MARIO_DISTANCE_X 93
#define MARIO_DISTANCE_Y 96

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING_UP	300
#define MARIO_STATE_WALKING_DOWN	400

#define NODE_WIDTH 58
#define NODE_HEIGHT 48

#define NODE_1_X 180
#define NODE_1_Y 48
#define NODE_2_X 370
#define NODE_2_Y 48
#define NODE_3_X 470
#define NODE_3_Y 48
#define NODE_4_X 470
#define NODE_4_Y 192
#define NODE_5_X 170
#define NODE_5_Y 480
#define NODE_6_X 370
#define NODE_6_Y 480


#pragma region ANIMATION_ID

#define ID_ANI_MARIO 9990



#pragma endregion


#define MARIO_SMALL_BBOX_WIDTH  42
#define MARIO_SMALL_BBOX_HEIGHT 45

class CMarioOverworld : public CMario
{
	CNode* node;
	float maxVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	float start_y;
	float start_x;

	vector<LPGAMEOBJECT> nodes;

	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isWitchscene;
	BOOLEAN isWalkingX;
	BOOLEAN isWalkingY;
	DWORD dt;

public:
	CMarioOverworld(float x, float y) : CMario(x, y)
	{
		maxVx = 0.5f;
		maxVy = 0.5f;
		ax = 0.0f;
		ay = 0.0f;
		vx = 0.0f;
		vy = 0.0f;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		isWitchscene = false;
		isWalkingX = false;
		isWalkingY = false;
		start_y = y;
		start_x = x;
		node = (CNode*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetNode();

	}


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void startCheckNode();
};