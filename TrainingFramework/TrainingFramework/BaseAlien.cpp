#include "../TrainingFramework/stdafx.h"
#include "BaseAlien.h"

BaseAlien::BaseAlien(
	std::shared_ptr<Model> model,
	std::vector<std::shared_ptr<Texture>> textureVector,
	std::shared_ptr<Shaders> shader,
	std::vector<GLint> numFrames,
	std::vector<GLint> numActions,
	std::vector<GLint> currentAction,
	std::vector<GLfloat> frameTime
) : Animation(model, textureVector, shader, numFrames, numActions, currentAction, frameTime)
{
	m_isAlive = true;
	m_isHover = false;
	m_isClick = false;
	m_speed = 0.0f;
	m_currentTexture = m_textureVector[0];
}

void BaseAlien::SetAlienAnimation(int index)
{
	m_currentTexture = m_textureVector[index];
};

BaseAlien::BaseAlien()
{
	SetAliveStatus(true);
	m_isHover = false;
	m_isClick = false;
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
	///*
	if ((m_pos.x - m_width / 2.0f <= x) && (x <= m_pos.x + m_width/ 2.0f)
		&& (m_pos.y - m_height / 2.0f <= y)	&& (y <= m_pos.y + m_height / 2.0f)	
		&& bIsPressed && GetAliveStatus() )
	{
		printf("Clicked!\n");
		SetAliveStatus(false);
		SetAlienAnimation(1);
		return true;
	}

	return false;
	//*/
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