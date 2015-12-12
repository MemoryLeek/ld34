#include "TurnHandler.h"
#include "EntityManager.h"
#include "Entity.h"

TurnHandler::TurnHandler(EntityManager &entityManager)
	: m_entityManager(entityManager)
	, m_remaining(-1)
{

}

void TurnHandler::update(const float delta)
{
	if (m_remaining > 0)
	{
		raiseEvent(&ITurn::turnProgress, getRemainingDelta(delta));

		m_remaining -= delta;
	}
	else
	{
		raiseEvent(&ITurn::turnIdle, delta);
	}
}

void TurnHandler::execute()
{
	if (m_remaining <= 0)
	{
		m_remaining = TURN_LENGTH;

		raiseEvent(&ITurn::turnStart, 0);
	}
}

bool TurnHandler::isRunning() const
{
	return m_remaining >= 0;
}

float TurnHandler::getRemainingDelta(const float delta) const
{
	if (m_remaining - delta < 0)
	{
		return m_remaining;
	}

	return delta;
}

void TurnHandler::raiseEvent(Function function, const float delta)
{
	const auto &entities = m_entityManager.entities();

	for (Entity *entity : entities)
	{
		ITurn *turn = dynamic_cast<ITurn *>(entity);

		if (turn)
		{
			(turn->*function)(delta);
		}
	}
}
