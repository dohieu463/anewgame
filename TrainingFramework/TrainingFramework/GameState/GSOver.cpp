#include "../TrainingFramework/stdafx.h"
#include "GSOver.h"
#include "../TrainingFramework/stdafx.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "../TrainingFramework/GameState/GSMachine.h"

GSOver::GSOver()
{
	m_stateType = STATE_GAMEOVER;
}

GSOver::~GSOver()
{
}

void GSOver::Init()
{
	/*m_overBackground = std::make_shared<Object>("Sprite2D", "temp", "TriangleShader");
	m_overBackground->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_overBackground->Set2DPos((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);

	std::shared_ptr<GameButton> buttonRestart = std::make_shared<GameButton>("Sprite2D", "btn_exit", "TriangleShader", BUTTON_RESTART);
	buttonRestart->SetSize(150.f, 40.f);
	buttonRestart->Set2DPos((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2 + 50);
	m_buttonList.push_back(buttonRestart);

	std::shared_ptr<GameButton> buttonScore = std::make_shared<GameButton>("Sprite2D", "btn_start", "TriangleShader", BUTTON_SCORE);
	buttonScore->SetSize(150.f, 40.f);
	buttonScore->Set2DPos((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_buttonList.push_back(buttonScore);

	std::shared_ptr<GameButton> buttonBackMenu = std::make_shared<GameButton>("Sprite2D", "btn_start", "TriangleShader", BUTTON_BACK_TO_MENU);
	buttonBackMenu->SetSize(150.f, 40.f);
	buttonBackMenu->Set2DPos((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2 - 50);
	m_buttonList.push_back(buttonBackMenu);
	*/
}

void GSOver::Exit()
{
}

void GSOver::Pause()
{
}

void GSOver::Resume()
{
}

void GSOver::Update(float deltaTime)
{
	
}

void GSOver::Draw()
{
	/*m_overBackground->Draw();
	for (auto& button : m_buttonList)
		button->Draw();*/
}


void GSOver::HandleEvents()
{
}

void GSOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOver::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	/*for (auto& button : m_buttonList) {
		if (button->HandleTouchEvent(x, y, bIsPressed))
		{
			switch (button->m_type)
			{
			case BUTTON_RESTART:
				GSMachine::GetInstance()->PushState(StateType::STATE_PLAY);
				printf("Start clicked! ");
				break;
			case BUTTON_SCORE:
				//GSMachine::GetInstance()->Pause();
				exit(0);
			case BUTTON_BACK_TO_MENU:
				//GSMachine::GetInstance()->Pause();
				exit(0);
			default:
				break;
			}
		};
	}*/
}

void GSOver::HandleMouseMoveEvents(float x, float y)
{
}