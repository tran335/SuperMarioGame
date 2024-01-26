#pragma once
#include "GameObject.h"
#include "Mario.h"

#define ID_NUMBER_ZERO	1810
#define ID_NUMBER_ONE	1811
#define ID_NUMBER_TWO	1812
#define ID_NUMBER_THREE	1813
#define ID_NUMBER_FOUR	1814
#define ID_NUMBER_FIVE	1815
#define ID_NUMBER_SIX	1816
#define ID_NUMBER_SEVEN	1817
#define ID_NUMBER_EIGHT	1818
#define ID_NUMBER_NINE	1819

#define SCORE_CX 278
#define SCORE_CY 628

class Score : public CGameObject
{
protected:
	float x;
	float y;
	int score;
	CMario* mario;
public:
	Score(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0; t = 0; r = 0; b = 0; };
	void AddNumberZero();
};


