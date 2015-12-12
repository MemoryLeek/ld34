#include "TurnHandler.h"
#include "EntityManager.h"
#include "Entity.h"

TurnHandler::TurnHandler(EntityManager &entityManager)
	: m_entityManager(entityManager)
	, m_remaining(END)
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
		if (raiseEvent(&ITurn::turnEnd, delta))
		{
			m_remaining = END;
		}
	}
}

void TurnHandler::execute()
{
	if (m_remaining == END)
	{
		m_remaining = TURN_LENGTH;

		raiseEvent(&ITurn::turnStart, 0);
	}
}

bool TurnHandler::isRunning() const
{
	return m_remaining != END;
}

float TurnHandler::getRemainingDelta(const float delta) const
{
	if (m_remaining - delta < 0)
	{
		return m_remaining;
	}

	return delta;
}

bool TurnHandler::raiseEvent(Function function, const float delta)
{
	bool result = true;

	const auto &entities = m_entityManager.entities();

	for (Entity *entity : entities)
	{
		ITurn *turn = dynamic_cast<ITurn *>(entity);

		if (turn)
		{
			result &= (turn->*function)(delta);
		}
	}

	return result;
}
