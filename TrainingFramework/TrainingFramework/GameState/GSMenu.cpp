﻿#include "../TrainingFramework/stdafx.h"
#include "GSMenu.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "GSMachine.h"
#include "../TrainingFramework/GameObject/Text.h"
//#include "../Resources/Fonts/orbitron/"

GSMenu::GSMenu()
{
	m_stateType = STATE_MENU;
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	m_menuBackground = SceneManager::GetInstance()->GetObjectByID("menu_background");
	auto buttonStart = SceneManager::GetInstance()->GetButtonByID("button_start");
	m_buttonList.push_back(buttonStart);
	auto buttonExit = SceneManager::GetInstance()->GetButtonByID("button_exit");
	m_buttonList.push_back(buttonExit);
	m_text.GetTextPosition() = Vector2(560, 560); // Đặt vị trí của văn bản
	m_text.GetTextColor() = SDL_Color({ 0, 0, 0, 1 }); // Đặt màu sắc của văn bản
	m_text.GetTextSize() = 30; // Đặt kích thước của văn bản
	m_text.GetTextMessage() = "Your Text Message"; // Đặt nội dung văn bản
	m_text.Init("../Resources/Fonts/orbitron/Orbitron-Black.ttf");
	

	printf("This is menu\n");
}

void GSMenu::Exit()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Update(float deltaTime)
{
	for (auto& chara : m_someAnim)
	{
		chara->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_menuBackground->Draw();
	for (auto& button : m_buttonList)
	{
		button->Draw();
	}
	for (auto& chara : m_someAnim)
	{
		chara->Draw();
	}
	m_text.Draw();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto& button : m_buttonList)
	{
		if (button->HandleTouchEvent(x, y, bIsPressed))
		{
			switch (button->m_type)
			{
			case BUTTON_START:
				GSMachine::GetInstance()->PushState(StateType::STATE_PLAY);
				printf("Start clicked! ");
				break;
			case BUTTON_EXIT:
				exit(0);
			default:
				break;
			}
		};
	}
}

void GSMenu::HandleMouseMoveEvents(float x, float y)
{
	for (auto& button : m_buttonList)
	{
		button->HandleMoveEvent(x, y);
	}
}