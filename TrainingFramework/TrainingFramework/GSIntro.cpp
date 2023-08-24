#include "stdafx.h"
#include "GSIntro.h"
#include "ResourceManager.h"
#include "Globals.h"
#include "GSMachine.h"
#include "SceneManager.h"


GSIntro::GSIntro()
{
	m_stateType = STATE_INTRO;
	m_ftime = 2;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	std::shared_ptr<Camera> m_camera = SceneManager::GetInstance()->GetCamera("smth");
	auto model = ResourceManager::GetInstance()->GetModelPointerByID("0");
	auto texture = ResourceManager::GetInstance()->GetTexturePointerByID("0");
	auto shader = ResourceManager::GetInstance()->GetShaderPointerByID("0");

	m_intro = std::make_shared<Object>(model, texture, shader);
	//m_intro->Init(model, texture, shader);
	m_intro->SetCamera(m_camera);

	m_intro->SetSize(0.05f, 0.05f);
	m_intro->SetPos(Vector3(0.0, 0.0, 0.0));
	printf("This is intro\n");
	printf("Gonna draw smth\n");
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