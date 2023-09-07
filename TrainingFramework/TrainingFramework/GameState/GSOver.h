#pragma once
#include "../TrainingFramework/GameState/GSBase.h"
#include "../TrainingFramework/GameObject/Object.h"
#include "../TrainingFramework/GameObject/Animation.h"
#include "../TrainingFramework/GameObject/GameButton.h"
#include "../BaseAlien.h"
class GSOver :
    public GSBase
{
public:
	GSOver();
	~GSOver();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
private:
	std::shared_ptr<Object> m_overBackground;
	std::vector<std::shared_ptr<BaseAlien>> m_overAnimation;
	std::vector<std::shared_ptr<GameButton>> m_buttonList;
};

