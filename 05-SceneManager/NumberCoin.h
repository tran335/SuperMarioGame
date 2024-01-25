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

#define COIN_CX 470
#define COIN_CY 605

class NumberCoin : public CGameObject
{
protected:
	float x;
	float y;
	CMario* mario;
	int coin;
public:
	NumberCoin(float x, float y);
	void Update();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0; t = 0; r = 0; b = 0; };
};

