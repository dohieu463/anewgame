#pragma once
#include "SingletonClass.h"
#include <list>

class GSBase;

enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY
};
class GSMachine : public SingletonClass<GSMachine>
{
public:
	GSMachine();
	~GSMachine();

	void	Cleanup();

	void	ChangeState(std::shared_ptr<GSBase> state);
	void	ChangeState(StateType stt);
	void	PushState(StateType stt);
	void	PopState();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	PerformStateChange();

	inline std::shared_ptr<GSBase> CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool HasState()const
	{
		return m_StateStack.size() > 0;
	}

private:
	std::list <std::shared_ptr<GSBase>>	m_StateStack;
	std::shared_ptr<GSBase>				m_pActiveState;
	std::shared_ptr<GSBase>				m_pNextState;
	bool	m_running;
	bool	m_fullscreen;
};

