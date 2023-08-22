#include "stdafx.h"
#include "GSBase.h"
#include<memory>
GSBase::GSBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GSBase> GSBase::CreateState(StateType stt)
{
	std::shared_ptr<GSBase> gameStatePtr = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		
		break;
	case StateType::STATE_INTRO:
		//gameStatePtr = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		//gameStatePtr = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		//gameStatePtr = std::make_shared<GSPlay>();
		break;
	//...
	}
	return gameStatePtr;
}

StateType GSBase::GetGameStateType()
{
	return m_stateType;
}