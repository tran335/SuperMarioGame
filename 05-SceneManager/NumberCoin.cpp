#include "NumberCoin.h"
#include "PlayScene.h"
NumberCoin::NumberCoin(float x, float y)
{
	this->x = x;
	this->y = y;
	coin = 0;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void NumberCoin::Update()
{

}

void NumberCoin::Render()
{
	CGame::GetInstance()->GetCamPos(x, y);
	//coin = mario->GetCoin();
	coin = 25;
	int aniId = -1;
	CAnimations* animations = CAnimations::GetInstance();
	
 if (coin >= 0 && coin < 10) {
		switch (coin)
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
		animations->Get(aniId)->Render(x + COIN_CX, y + COIN_CY);
	}
 else {
	 
	 switch (coin / 10)
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
	 animations->Get(aniId)->Render(x + COIN_CX-24, y + COIN_CY);

	 switch (coin % 10)
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
	 animations->Get(aniId)->Render(x + COIN_CX, y + COIN_CY);
 }

	/*CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x + COIN_CX, y + COIN_CY);
	animations->Get(aniId)->Render(x + COIN_CX-50, y + COIN_CY-50);*/
}

