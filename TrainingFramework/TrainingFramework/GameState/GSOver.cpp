#include "../TrainingFramework/stdafx.h"
#include "GSOver.h"
#include "../TrainingFramework/stdafx.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "../TrainingFramework/GameState/GSMachine.h"
#include "../TrainingFramework/GameObject/Text.h"

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
	m_buttonList.push_back(SceneManager::GetInstance()->GetButtonByID("button_restart"));
	m_buttonList.push_back(SceneManager::GetInstance()->GetButtonByID("button_back_to_menu"));
	m_buttonList.push_back(SceneManager::GetInstance()->GetButtonByID("button_score"));
	m_text.SetPos({ 640, 190, 1 }); // Đặt vị trí của văn bản
	m_text.GetTextColor() = SDL_Color({ 255, 0, 0, 255 }); // Đặt màu sắc của văn bản
	m_text.GetTextSize() = 80; // Đặt kích thước của văn bản
	m_text.GetTextMessage() = "GAME OVER"; // Đặt nội dung văn bản
	m_text.Init("../Resources/Fonts/orbitron/Orbitron-Black.ttf");
	AddSoundByName("tu_sena");
	PlaySingleSoundByName("tu_sena");
}

void GSOver::Exit()
{
	StopSoundByName("tu_sena");
}

void GSOver::Pause()
{
	PauseSoundByName("tu_sena");
}

void GSOver::Resume()
{
	ResumeSoundByName("tu_sena");
}

void GSOver::Update(float deltaTime)
{
	
}

void GSOver::Draw()
{
	m_overBackground->Draw();
	m_text.Draw();
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