#include "stdafx.h"
#include "GameButton.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) 
{
	m_isHolding = false;
	m_isClick = false;
}

GameButton::GameButton()
{
	m_isHolding = false;
	m_isClick = false;
}

GameButton::~GameButton()
{
}

bool GameButton::HandleTouchEvent(GLfloat x, GLfloat y, bool bIsPressed)
{
	if ((m_pos.x - m_width / 2.0f <= x) && (x <= m_pos.x + m_width / 2.0f)
		&& (m_pos.y - m_height / 2.0f <= y) && (y <= m_pos.y + m_height / 2.0f)
		&& bIsPressed)
	{
		m_alpha = 2.0f;
		return true;
	}

	m_alpha = 1.0f;

	return false;
}

void GameButton::HandleMoveEvent(GLfloat x, GLfloat y)
{
	if ((m_pos.x - m_width / 2.0f <= x) && (x <= m_pos.x + m_width / 2.0f)
		&& (m_pos.y - m_height / 2.0f <= y) && (y <= m_pos.y + m_height / 2.0f))
	{
		m_isHolding = true;
		m_alpha = 0.8f;
	}
	else
	{
		m_alpha = 1.0f;
	}
}

bool GameButton::IsHolding() 
{
	return m_isHolding;
}