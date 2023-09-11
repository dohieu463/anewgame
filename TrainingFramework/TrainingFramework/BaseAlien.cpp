#include "../TrainingFramework/stdafx.h"
#include "BaseAlien.h"

BaseAlien::BaseAlien(
	std::shared_ptr<Model> model,
	std::vector<std::shared_ptr<Texture>> textureVector,
	std::shared_ptr<Shaders> shader,
	std::vector<GLint> numFrames,
	std::vector<GLint> numActions,
	std::vector<GLint> currentAction,
	std::vector<GLfloat> frameTime,
	float speed,
	int health,
	int score
) : Animation(model, textureVector, shader, numFrames, numActions, currentAction, frameTime)
{
	m_speed = speed;
	m_health = health;
	m_score = score;
	m_isAlive = true;
	m_isHover = false;
	m_isClick = false;
	m_currentTexture = m_textureVector[0];
}

void BaseAlien::SetAlienAnimation(int index)
{
	m_currentTexture = m_textureVector[index];
};

BaseAlien::BaseAlien()
{
	m_health = 1;
	m_score = 1;
	m_speed = 1;
	m_isAlive = true;
	m_isHover = false;
	m_isClick = false;
}

BaseAlien::BaseAlien(const BaseAlien& other)
{
	this->m_objectID = other.m_objectID;
	this->m_model = other.m_model;
	this->m_currentTexture = other.m_currentTexture;
	this->m_textureVector = other.m_textureVector;
	this->m_shader = other.m_shader;
	this->m_camera = other.m_camera;

	this->Set2DPos(other.m_pos.x, other.m_pos.y);
	this->SetSize(other.m_scale.x, other.m_scale.y);
	
	this->m_alpha = other.m_alpha;
	this->m_width = other.m_width;
	this->m_height = other.m_height;

	this->m_numFrames = other.m_numFrames;
	this->m_currentFrame = other.m_currentFrame;
	this->m_frameTime = other.m_frameTime;
	this->m_currentTime = other.m_currentTime;
	this->m_numActions = other.m_numActions;
	this->m_currentAction = other.m_currentAction;

	this->m_numFramesVector = other.m_numFramesVector;
	this->m_frameTimeVector = other.m_frameTimeVector;
	this->m_numActionsVector = other.m_numActionsVector;
	this->m_currentActionVector = other.m_currentActionVector;

	this->m_isAlive = other.m_isAlive;
	this->m_isHover = other.m_isHover;
	this->m_isClick = other.m_isClick;
	this->m_speed = other.m_speed;
	this->m_health = other.m_health;
	this->m_score = other.m_score;
}

void BaseAlien::UpdatePos(float deltaTime, float difficult)
{
	// Tính toán sự biến đổi trong hướng X và Y
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	deltaX = m_speed * deltaTime * difficult;
	deltaY = (rand() % 9 - 4) * difficult; // Số ngẫu nhiên trong khoảng [-4, 4]

	m_pos.x += deltaX;
	m_pos.y += deltaY;

	if (m_pos.y <= 120) m_pos.y += 2 * deltaY;
	if (m_pos.y >= 960) m_pos.y -= 2 * deltaY;

	return;
}

BaseAlien::~BaseAlien()
{
}

void BaseAlien::SetAliveStatus(bool status)
{
	m_isAlive = status;
}

bool BaseAlien::HandleTouchEvent(GLfloat x, GLfloat y, bool bIsPressed)
{
	if ((m_pos.x - m_width / 2.0f <= x) && (x <= m_pos.x + m_width/ 2.0f)
		&& (m_pos.y - m_height / 2.0f <= y)	&& (y <= m_pos.y + m_height / 2.0f)	
		&& bIsPressed && GetAliveStatus() )
	{
		printf("Clicked but not dead!\n");
		m_health--;
		if (m_health == 0) 
		{
			SetAliveStatus(false);
			SetAlienAnimation(2);
			return true;
		}
	}
	return false;
}

void BaseAlien::HandleMoveEvent(GLfloat x, GLfloat y)
{
	/*
	if ((m_pos.x - m_width / 2.0f <= x) && (x <= m_pos.x + m_width / 2.0f)
		&& (m_pos.y - m_height / 2.0f <= y) && (y <= m_pos.y + m_height / 2.0f))
	{
		m_isHover = true;
		m_alpha = 0.8f;
	}
	else
	{
		m_alpha = 1.0f;
	}
	*/
}

bool BaseAlien::IsHover()
{
	return m_isHover;
}