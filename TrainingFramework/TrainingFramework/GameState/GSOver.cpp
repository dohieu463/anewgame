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
	m_overBackground = SceneManager::GetInstance()->GetObjectByID("over_background");
	auto buttonRestart = SceneManager::GetInstance()->GetButtonByID("button_restart");
	m_buttonList.push_back(buttonRestart);
	auto buttonBackMenu = SceneManager::GetInstance()->GetButtonByID("button_back_to_menu");
	m_buttonList.push_back(buttonBackMenu);
	auto buttonScore = SceneManager::GetInstance()->GetButtonByID("button_score");
	m_buttonList.push_back(buttonScore);
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
	m_overBackground->Draw();
	for (auto& button : m_buttonList)
		button->Draw();
}


void GSOver::HandleEvents()
{
}

void GSOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOver::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto& button : m_buttonList) {
		if (button->HandleTouchEvent(x, y, bIsPressed))
		{
			switch (button->m_type)
			{
			case BUTTON_RESTART:
				GSMachine::GetInstance()->PushState(StateType::STATE_PLAY);
				break;
			case BUTTON_BACK_TO_MENU:
				GSMachine::GetInstance()->PushState(StateType::STATE_MENU);
				break;
			case BUTTON_SCORE:
				GSMachine::GetInstance()->PushState(StateType::STATE_SCORE);
				break;
			}
		};
	}
}

void GSOver::HandleMouseMoveEvents(float x, float y)
{
	for (auto& button : m_buttonList)
	{
		button->HandleMoveEvent(x, y);
	}
}