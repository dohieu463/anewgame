#include "../TrainingFramework/stdafx.h"
#include "GSPlay.h"
#include "../TrainingFramework/stdafx.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include "../TrainingFramework/GameState/GSMachine.h"
#include "../Random.h"
float animationX = 50;
float animationY = (float)Globals::screenHeight / 2; 
int alienCount = 0;
float m_time = 1;
float lives = 3;
GSPlay::GSPlay()
{
	m_stateType = STATE_PLAY;
	
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	m_playBackground = SceneManager::GetInstance()->GetObjectByID("play_background");
	m_base = SceneManager::GetInstance()->GetObjectByID("human_base");
	printf("This is play\n");
	//Spawn();
}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::Update(float deltaTime)
{
	///*
	m_time -= deltaTime;
	if (m_time <= 0) {
		m_time += 1;
		Spawn();
	}

	std::vector<std::shared_ptr<BaseAlien>> aliveAlien;

	for (auto& alien : m_alien) {
		float animationX = alien->GetPos().x;
		float animationY = alien->GetPos().y;
		if (alien->GetAliveStatus()) 
		{
			animationX += 60 * deltaTime;

			int random_number = distribution(generator);
			if (random_number % 2 == 0)
			{
				animationY += 5;
				if (animationY >= 600) animationY -= 5;
			}
			
			else 
			{
				animationY -= 5;
				if (animationY <= 120) animationY += 5;
			}
			
			if (animationX > Globals::screenWidth - 60) {
				alienCount--;
				lives--;
				if (lives == 0) GSMachine::GetInstance()->PushState(StateType::STATE_GAMEOVER);
			}
			else
			{
				alien->Set2DPos(animationX, animationY);
				alien->Update(deltaTime);
				aliveAlien.push_back(alien);
			}
		}
		else 
		{
			alien->Update(deltaTime);
			aliveAlien.push_back(alien);
		}
	}	
	m_alien = aliveAlien;
	//*/
}

void GSPlay::Draw()
{
	m_playBackground->Draw();
	m_base->Draw();
	for (auto& alien : m_alien)
		alien->Draw();
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto& alien : m_alien) {
		if (alien->HandleTouchEvent(x, y, bIsPressed)) alienCount--;
	}
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
}

void GSPlay::Spawn() 
{
	if (alienCount == 10) return;
	auto new_alien = SceneManager::GetInstance()->GetAlienByID("alien2");
	auto alien = std::make_shared<BaseAlien>(*new_alien);
	float animationX = 50;
	float animationY = (float)Globals::screenHeight / 2 + (distribution(generator) % 5) * 120 - 240;
	alien->Set2DPos(animationX, animationY);

	m_alien.push_back(alien);
	alienCount++;
}