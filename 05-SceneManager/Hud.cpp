#include "HUD.h"
#include "PlayScene.h"

Hud::Hud(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Hud::Update()
{

}

void Hud::Render()
{
	//DebugOut(L"Render hud ne");
	CGame::GetInstance()->GetCamPos(x, y);

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_HUD)->Render(x + HUD_CX, y + HUD_CY);
	power->Render();
	numbercoin->Render();
}
