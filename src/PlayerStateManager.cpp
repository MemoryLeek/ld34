#include "PlayerStateManager.h"

PlayerState::PlayerState()
	: m_isGoalReached(false)
{

}

bool PlayerState::isGoalReached() const
{
	return m_isGoalReached;
}

void PlayerState::setIsGoalReached(bool isGoalReached)
{
	m_isGoalReached = isGoalReached;
}

