#include "../TrainingFramework/stdafx.h"
#include "GSBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSOver.h"
#include "GSScore.h"

GSBase::GSBase()
{
}

GSBase::GSBase(StateType stateType) : m_stateType(stateType)
{
}

GSBase::~GSBase() 
{
}

std::shared_ptr<GSBase> GSBase::CreateState(StateType stateType)
{
	std::shared_ptr<GSBase> state;
	switch (stateType)
	{
	case STATE_INVALID:
		break;
	case STATE_INTRO:
		return std::make_shared<GSIntro>();
	case STATE_MENU:
		return std::make_shared<GSMenu>();
	case STATE_PLAY:
		return std::make_shared<GSPlay>();
	case STATE_GAMEOVER:
		return std::make_shared<GSOver>();
	case STATE_SCORE:
		return std::make_shared<GSScore>();
	default:
		break;
	}
	return nullptr;
}

StateType GSBase::GetGameStateType()
{
	return m_stateType;
}
