#pragma once
#include "GameObject.h"
#include "BrickCoin.h"
#include "Items.h"


#define QUESTIONBRICK_STATE_NORMAL 1100
#define QUESTIONBRICK_STATE_DISABLE 1200

#define ID_ANI_QUESTIONBRICK_NORMAL  7000
#define ID_ANI_QUESTIONBRICK_DISABLE 7001

#define QUESTIONBRICK_BBOX_WIDTH 48
#define QUESTIONBRICK_BBOX_HEIGHT 48 

#define QUESTIONBRICK_JUMP_Y		10.0f


class CQuestionbrick : public CGameObject
{
protected:
	float x,y, start_y;
	int item_type;
	ULONGLONG throwup_start;
	int isThrow = 0;
	BOOLEAN hasItem;
public:
	CQuestionbrick(float x, float y, int item_type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b); 
	void SetState(int state);
	void StartThrowup(){ throwup_start = GetTickCount64(); }
	void GetIsThrow(int isThow) { isThrow = this->isThrow; };
	
};

