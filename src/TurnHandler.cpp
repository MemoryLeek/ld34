#include "TurnHandler.h"
#include "EntityManager.h"
#include "Entity.h"

TurnHandler::TurnHandler(EntityManager &entityManager)
	: m_entityManager(entityManager)
{

}

void TurnHandler::execute()
{
	const auto &entities = m_entityManager.entities();

	for (Entity *entity : entities)
	{
		entity->execute();
	}
}
