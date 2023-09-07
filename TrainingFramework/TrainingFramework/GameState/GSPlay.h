#pragma once
#include "../TrainingFramework/GameState/GSBase.h"
#include "../TrainingFramework/GameObject/Object.h"
#include "../TrainingFramework/GameObject/Animation.h"
#include "../TrainingFramework/GameObject/GameButton.h"
#include "../BaseAlien.h"

void UpdateScore(std::vector<int>& scores, int currentScore);
class GSPlay :
    public GSBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	void	Spawn();

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
private:
	std::shared_ptr<Object> m_playBackground;
	std::shared_ptr<Object> m_base;
	std::vector<std::shared_ptr<BaseAlien>> m_alien;

	int alienCount = 0;
	float m_time = 1;
	float lives = 3;
	int alienSpawned = 0;
	int score = 0;
};

