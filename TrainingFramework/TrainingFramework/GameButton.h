#pragma once
#include "Object.h"
class GameButton : public Object
{
public:
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	GameButton();
	~GameButton();

	bool HandleTouchEvent(GLfloat x, GLfloat y, bool bIsPressed);
	void HandleMoveEvent(GLfloat x, GLfloat y);
	bool IsHolding();
private:

	bool m_isHolding;
	bool m_isClick;
};

