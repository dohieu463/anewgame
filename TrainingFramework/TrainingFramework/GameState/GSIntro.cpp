#include "../TrainingFramework/stdafx.h"
#include "GSIntro.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "GSMachine.h"
#include "../TrainingFramework/GameManager/SceneManager.h"


GSIntro::GSIntro()
{
	m_stateType = STATE_INTRO;
	m_ftime = 0.5;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	m_intro = SceneManager::GetInstance()->GetObjectByID("intro_logo");
}

void GSIntro::Exit()
{
}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Update(float deltaTime)
{
	m_ftime -= deltaTime;
	if (m_ftime < 0)
	{
		GSMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
	}
}

void GSIntro::Draw()
{
	m_intro->Draw();
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSIntro::HandleTouchEvents(float x, float y, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(float x, float y)
{
}