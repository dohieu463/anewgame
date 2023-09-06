#pragma once
#include "GameObject/Animation.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "Globals.h"

class BaseAlien : public Animation
{
public:
	BaseAlien::BaseAlien(
		std::shared_ptr<Model> model,
		std::vector<std::shared_ptr<Texture>> textureVector,
		std::shared_ptr<Shaders> shader,
		std::vector<GLint> numFrames,
		std::vector<GLint> numActions,
		std::vector<GLint> currentAction,
		std::vector<GLfloat> frameTime
	);
	BaseAlien();
	virtual ~BaseAlien();

	bool HandleTouchEvent(GLfloat x, GLfloat y, bool bIsPressed);
	void HandleMoveEvent(GLfloat x, GLfloat y);
	bool IsHover();

	void SetAliveStatus(bool status);
	bool GetAliveStatus() { return m_isAlive; };
	void SetAlienAnimation(int index);
private:
	bool m_isAlive;
	bool m_isHover;
	bool m_isClick;
	float m_speed;
};

