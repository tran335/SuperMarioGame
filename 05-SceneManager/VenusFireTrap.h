#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "FireBall.h"

#define VENUS_BBOX_WIDTH 48
#define VENUS_BBOX_HEIGHT 95
#define VENUS_HEIGHT 70
#define VENUS_WIDTH 70

#define IC_ANI_VENUS_DOWN_LEFT 8011
#define ID_ANI_VENUS_UP_LEFT 802
#define ID_ANI_VENUS_SHOOT_DOWN_LEFT 803
#define ID_ANI_VENUS_SHOOT_UP_LEFT 804

#define IC_ANI_VENUS_DOWN_RIGHT 805
#define ID_ANI_VENUS_UP_RIGHT 806
#define ID_ANI_VENUS_SHOOT_DOWN_RIGHT 807
#define ID_ANI_VENUS_SHOOT_UP_RIGHT 808

#define VENUS_SPEED 2.0f

#define VENUS_SHOOTING_TIME 4000

#define RED_VENUS 1
#define GREEN_VENUS 2

class CVenusFireTrap : public CGameObject
{
	float x, y, start_y;
	int type;
	bool isShooting = false;
	bool isUp = false;
	bool isRight = false;
	bool isStop = false;
	ULONGLONG shootingTime;
	CMario* mario = NULL;
	CFireBall* fireball;
public:
	CVenusFireTrap(float x, float y, int type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void startShootingTime() { isShooting = true, shootingTime = GetTickCount64(); fireball = new CFireBall(x, y); }
};

