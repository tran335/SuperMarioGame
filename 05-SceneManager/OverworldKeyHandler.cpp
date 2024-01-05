#include "OverworldKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "MarioOverworld.h"
#include "PlayScene.h"

void COverworldKeyHandler::OnKeyDown(int KeyCode)
{
	CMarioOverworld* mario = (CMarioOverworld*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_1:
		CGame::GetInstance()->InitiateSwitchScene(INTRO_SCENE);
		break;
	case DIK_2:
		CGame::GetInstance()->InitiateSwitchScene(OVERWORLD_SCENE);
		break;
	case DIK_3:
		CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_1_1_SCENE);
		break;
	/*case DIK_S:
		CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_1_1_SCENE);
		break;*/
	case DIK_RIGHT:
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
		break;
	case DIK_LEFT:
		mario->SetState(MARIO_STATE_WALKING_LEFT);
		break;
	case DIK_UP:
		mario->SetState(MARIO_STATE_WALKING_UP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_WALKING_DOWN);
		break;
	}
}

