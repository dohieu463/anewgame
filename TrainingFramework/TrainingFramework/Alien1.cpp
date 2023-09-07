#include "../TrainingFramework/stdafx.h"
#include "Alien1.h"
Alien1::Alien1() 
{
	SceneManager::GetInstance()->GetAlienByID("alien1");
	m_model = ResourceManager::GetInstance()->GetModelPointerByName("Sprite2D");
	auto texture = ResourceManager::GetInstance()->GetTexturePointerByName("mobAlien1_run");
	m_textureVector.push_back(texture);
	texture = ResourceManager::GetInstance()->GetTexturePointerByName("mobAlien1_idle");
	m_textureVector.push_back(texture);
	m_shader = ResourceManager::GetInstance()->GetShaderPointerByName("Animation");
	
	m_numFrames = 4;
	m_numActions = 1;
	m_currentAction = 0;
	m_frameTime = 0.2f;
	m_currentFrame = 0;
	m_currentTime = 0;
}

Alien1::~Alien1() 
{
}