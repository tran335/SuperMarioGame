#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Sprite.h"
#include "Power.h"
#include "NumberCoin.h"
#include "TimeLimit.h"
#include "Score.h"

#define ID_HUD 111112

#define HUD_CX 368
#define HUD_CY 610

class Hud : public CGameObject
{
protected:
	float x;
	float y;
	int coin;
	Power* power = new Power(x, y);
	NumberCoin* numbercoin = new NumberCoin(x, y);
	TimeLimit* timelimit = new TimeLimit(x, y);
	Score* score = new Score(x, y);
public:
	Hud(float x, float y);
	void Update();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0; t = 0; r = 0; b = 0; };
};

