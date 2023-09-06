#pragma once
#include "../TrainingFramework/stdafx.h"
#include <memory>

enum StateType {
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	STATE_GAMEOVER,
};

class GSBase
{
public:
	GSBase();
	GSBase(StateType stateType);
	virtual ~GSBase();
	
	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(float x, float y, bool bIsPressed) = 0;
	virtual void HandleMouseMoveEvents(float x, float y) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	static std::shared_ptr<GSBase> CreateState(StateType stt);
	StateType GetGameStateType();

protected:
	StateType	m_stateType;
};

