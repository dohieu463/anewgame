#pragma once
#include "GSBase.h"
#include "../TrainingFramework/GameObject/Object.h"
#include "../TrainingFramework/GameObject/Animation.h"
#include "../TrainingFramework/GameObject/GameButton.h"
#include "../BaseAlien.h"
#include "GSMachine.h"
#include "../TrainingFramework/GameManager/SceneManager.h"
#include "../TrainingFramework/GameManager/ResourceManager.h"
#include "../TrainingFramework/Globals.h"
#include <cstdlib>

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

	void	Spawn(const char* type);
	void	UpdateDifficult();
	void	SpawnByDifficult(float deltaTime);
	void	GunUpdate(float deltaTime);
	
	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
private:
	std::shared_ptr<Object> m_playBackground;
	std::shared_ptr<Object> m_base;
	std::vector<std::shared_ptr<BaseAlien>> m_alien;
	std::shared_ptr<Animation> m_loadingAnimation;
	std::vector<std::shared_ptr<GameButton>> m_buttonList;

	int alienCount;
	float m_time;
	float lives;
	int alienSpawned;
	int score;
	float m_mobAlienRate;
	float m_medAlienRate;
	float m_highAlienRate;
	float m_bullets;
	float m_gunReloadTime;
	float m_reloadTime;
	bool isBulletOut;
};