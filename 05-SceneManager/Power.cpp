#include "Power.h"
#include "PlayScene.h"

Power::Power(float x, float y)
{
	this->x = x;
	this->y = y;
	mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void Power::Update()
{

}

void Power::Render()
{
	//DebugOut(L"Render power ne");
	CGame::GetInstance()->GetCamPos(x, y);
	float vx_mario, vy_mario;
	mario->GetSpeed(vx_mario, vy_mario);
    
	int aniId = -1;

	if (abs(vx_mario) >= VX_6) aniId = ID_ANI_POWER_6;
	else if (abs(vx_mario) >= VX_5) aniId = ID_ANI_POWER_5;
	else if (abs(vx_mario) >= VX_4) aniId = ID_ANI_POWER_4;
	else if (abs(vx_mario) >= VX_3) aniId = ID_ANI_POWER_3;
	else if (abs(vx_mario) >= VX_2) aniId = ID_ANI_POWER_2;
	else if (abs(vx_mario) >= VX_1) aniId = ID_ANI_POWER_1;
	else aniId = ID_ANI_POWER_0;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x + POWER_CX, y + POWER_CY);
}

