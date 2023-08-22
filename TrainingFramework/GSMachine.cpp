#include "stdafx.h"
#include "GSMachine.h"
#include "GSBase.h"

GSMachine::GSMachine() : m_running(true), m_pActiveState(nullptr), m_pNextState(nullptr), m_fullscreen(false)
{
}


GSMachine::~GSMachine()
{
}


void GSMachine::Cleanup()
{
	while (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}
}

void GSMachine::ChangeState(StateType state)
{
	std::shared_ptr<GSBase> nextState = GSBase::CreateState(state);
	ChangeState(nextState);
}

void GSMachine::ChangeState(std::shared_ptr<GSBase> state)
{
	m_pNextState = state;
}

void GSMachine::PushState(StateType state)
{
	std::shared_ptr<GSBase> nextState = GSBase::CreateState(state);
	// pause current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}

	m_pNextState = nextState;
}

void GSMachine::PopState()
{
	// cleanup the current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}

	// resume previous state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
		m_pActiveState = m_StateStack.back();
	}
}

void  GSMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		if (m_StateStack.empty() == false) {
			if (m_pActiveState->GetGameStateType() == StateType::STATE_INTRO)
			{
				// Cleanup Intro state
				m_pActiveState->Exit();
				m_StateStack.pop_back();
			}
			else
			{
				// Pause other states
				m_pActiveState->Pause();
			}
		}

		// store and init the new state
		m_StateStack.push_back(m_pNextState);
		m_StateStack.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}