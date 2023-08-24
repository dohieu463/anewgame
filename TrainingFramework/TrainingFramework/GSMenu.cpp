#include "stdafx.h"
#include "GSMenu.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Globals.h"
#include "GSMachine.h"


GSMenu::GSMenu()
{
	m_stateType = STATE_INTRO;
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	///*
	std::shared_ptr<Camera> m_camera = SceneManager::GetInstance()->GetCamera("");
	auto model = ResourceManager::GetInstance()->GetModelPointerByID("1");
	auto texture = ResourceManager::GetInstance()->GetTexturePointerByID("1");
	auto shader = ResourceManager::GetInstance()->GetShaderPointerByID("0");

	m_menuBackground = std::make_shared<Object>(model, texture, shader);
	m_menuBackground->SetCamera(m_camera);
	m_menuBackground->SetSize((float)Globals::screenWidth, (float)Globals::screenHeight);
	m_menuBackground->SetPos(Vector3((float)Globals::screenWidth / 2.0, (float)Globals::screenHeight / 2.0f, 0.0f));
	printf("This is menu\n");
	
	//*/
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
	
}

void GSMenu::Draw()
{
	m_menuBackground->Draw();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(float x, float y, bool bIsPressed)
{
}

void GSMenu::HandleMouseMoveEvents(float x, float y)
{
}