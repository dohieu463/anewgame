#pragma once
#include "Object.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include <map>
#include <unordered_map>

enum ButtonType 
{
	BUTTON_START,
	BUTTON_EXIT,
	BUTTON_BACK_TO_MENU,
	BUTTON_SCORE,
	BUTTON_PAUSE,
	BUTTON_RESUME,
	BUTTON_RESTART,
	DEFAULT_BUTTON
};
class GameButton : public Object
{
public:
	/*
	GameButton(
		std::shared_ptr<Model> model, 
		std::shared_ptr<Texture> texture, 
		std::shared_ptr<Shaders> shader,
		const char* type
	);
	*/
	GameButton(
		const char* modelName,
		const char* textureName,
		const char* shaderName,
		const char* type
	);
	GameButton();
	~GameButton();

	bool HandleTouchEvent(GLfloat x, GLfloat y, bool bIsPressed);
	void HandleMoveEvent(GLfloat x, GLfloat y);
	void SetButtonType(ButtonType buttonType);
	bool IsHover();
	ButtonType GetButtonType() { return m_type; };
	ButtonType m_type;

	ButtonType StringToButtonType(const char* buttonTypeStr);

private:

	bool m_isHover;
	bool m_isClick;
};