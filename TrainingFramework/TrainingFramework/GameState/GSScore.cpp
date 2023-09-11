#include "../TrainingFramework/stdafx.h"
#include "GSScore.h"
#include "../TrainingFramework/stdafx.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "../TrainingFramework/GameState/GSMachine.h"

GSScore::GSScore()
{
	m_stateType = STATE_SCORE;
}

GSScore::~GSScore()
{
}

void GSScore::Init()
{
	m_scoreBackground = SceneManager::GetInstance()->GetObjectByID("over_background");
	auto buttonRestart = SceneManager::GetInstance()->GetButtonByID("button_restart");
	m_buttonList.push_back(buttonRestart);
	auto buttonBackMenu = SceneManager::GetInstance()->GetButtonByID("button_back_to_menu");
	m_buttonList.push_back(buttonBackMenu);
}

void GSScore::Exit()
{
}

void GSScore::Pause()
{
}

void GSScore::Resume()
{
}

void GSScore::Update(float deltaTime)
{

}

void GSScore::Draw()
{
	m_scoreBackground->Draw();
	for (auto& button : m_buttonList)
		button->Draw();
}


void GSScore::HandleEvents()
{
}

void GSScore::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSScore::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto& button : m_buttonList) {
		if (button->HandleTouchEvent(x, y, bIsPressed))
		{
			switch (button->m_type)
			{
			case BUTTON_RESTART:
				break;
			case BUTTON_SCORE:
				break;
			case BUTTON_BACK_TO_MENU:
				break;
			}
		};
	}
}

void GSScore::HandleMouseMoveEvents(float x, float y)
{
	for (auto& button : m_buttonList)
	{
		button->HandleMoveEvent(x, y);
	}
}