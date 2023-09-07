﻿#include "../TrainingFramework/stdafx.h"
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
	m_currentTexture = m_textureVector[0];
}

void BaseAlien::SetAlienAnimation(int index)
{
	m_currentTexture = m_textureVector[index];
};

BaseAlien::BaseAlien()
{
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