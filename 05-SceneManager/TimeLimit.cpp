#include "TimeLimit.h"
#include "PlayScene.h"
TimeLimit::TimeLimit(float x, float y)
{
	this->x = x;
	this->y = y;
	remaining_time = 0;
	isTimeOut = false;
	start_time = GetTickCount64()/1000;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void TimeLimit::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isTimeOut = false;
	CGameObject::Update(dt, coObjects);
}

void TimeLimit::Render()
{
	CGame::GetInstance()->GetCamPos(x, y);
	int aniId = ID_NUMBER_ZERO;
	CAnimations* animations = CAnimations::GetInstance();
	if (!isTimeOut) RemainTime();
	time = remaining_time;
 
	if (time >= 0) {
		switch (time / 100)
		{
		case 0:
			aniId = ID_NUMBER_ZERO;
			break;
		case 1:
			aniId = ID_NUMBER_ONE;
			break;
		case 2:
			aniId = ID_NUMBER_TWO;
			break;
		case 3:
			aniId = ID_NUMBER_THREE;
			break;
		case 4:
			aniId = ID_NUMBER_FOUR;
			break;
		case 5:
			aniId = ID_NUMBER_FIVE;
			break;
		case 6:
			aniId = ID_NUMBER_SIX;
			break;
		case 7:
			aniId = ID_NUMBER_SEVEN;
			break;
		case 8:
			aniId = ID_NUMBER_EIGHT;
			break;
		case 9:
			aniId = ID_NUMBER_NINE;
			break;
		default:
			break;
		}
		animations->Get(aniId)->Render(x + TIME_CX - 48, y + TIME_CY);

		switch ((time % 100) / 10)
		{
		case 0:
			aniId = ID_NUMBER_ZERO;
			break;
		case 1:
			aniId = ID_NUMBER_ONE;
			break;
		case 2:
			aniId = ID_NUMBER_TWO;
			break;
		case 3:
			aniId = ID_NUMBER_THREE;
			break;
		case 4:
			aniId = ID_NUMBER_FOUR;
			break;
		case 5:
			aniId = ID_NUMBER_FIVE;
			break;
		case 6:
			aniId = ID_NUMBER_SIX;
			break;
		case 7:
			aniId = ID_NUMBER_SEVEN;
			break;
		case 8:
			aniId = ID_NUMBER_EIGHT;
			break;
		case 9:
			aniId = ID_NUMBER_NINE;
			break;
		default:
			break;
		}
		animations->Get(aniId)->Render(x + TIME_CX - 24, y + TIME_CY);

		switch (time % 10)
		{
		case 0:
			aniId = ID_NUMBER_ZERO;
			break;
		case 1:
			aniId = ID_NUMBER_ONE;
			break;
		case 2:
			aniId = ID_NUMBER_TWO;
			break;
		case 3:
			aniId = ID_NUMBER_THREE;
			break;
		case 4:
			aniId = ID_NUMBER_FOUR;
			break;
		case 5:
			aniId = ID_NUMBER_FIVE;
			break;
		case 6:
			aniId = ID_NUMBER_SIX;
			break;
		case 7:
			aniId = ID_NUMBER_SEVEN;
			break;
		case 8:
			aniId = ID_NUMBER_EIGHT;
			break;
		case 9:
			aniId = ID_NUMBER_NINE;
			break;
		default:
			break;
		}
	}
	animations->Get(aniId)->Render(x + TIME_CX, y + TIME_CY);
}

void TimeLimit::RemainTime()
{
	remaining_time = TIME_LIMIT - (GetTickCount64() / 1000 - start_time);
	if (remaining_time <= 0) 
	{
		isTimeOut = true;
		mario->SetState(MARIO_STATE_DIE);
		//CGame::GetInstance()->InitiateSwitchScene(2);
	}
}

