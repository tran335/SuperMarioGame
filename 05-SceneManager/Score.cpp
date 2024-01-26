#include "Score.h"
#include "PlayScene.h"
Score::Score(float x, float y)
{
	this->x = x;
	this->y = y;
	score = 0;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void Score::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
}

void Score::Render()
{
	CGame::GetInstance()->GetCamPos(x, y);
	int aniId = ID_NUMBER_ZERO;
	CAnimations* animations = CAnimations::GetInstance();
	score = mario->GetScore();
	int score_dv = score / 100;

	if (score_dv >= 0) {
		switch (score_dv / 100)
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
		animations->Get(aniId)->Render(x + SCORE_CX - 48, y + SCORE_CY);

		switch ((score_dv % 100) / 10)
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
		animations->Get(aniId)->Render(x + SCORE_CX - 24, y + SCORE_CY);

		switch (score_dv % 10)
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
	animations->Get(aniId)->Render(x + SCORE_CX, y + SCORE_CY);
	AddNumberZero();

}

void Score::AddNumberZero()
{
	int aniId = ID_NUMBER_ZERO;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x + SCORE_CX + 48, y + SCORE_CY);
	animations->Get(aniId)->Render(x + SCORE_CX + 24, y + SCORE_CY);
	animations->Get(aniId)->Render(x + SCORE_CX - 72, y + SCORE_CY);
	animations->Get(aniId)->Render(x + SCORE_CX - 96, y + SCORE_CY);
}

