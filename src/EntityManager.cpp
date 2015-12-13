#include "EntityManager.h"
#include "IEntity.h"

void EntityManager::add(IEntity *entity)
{
	m_entities.insert(entity);
}

void EntityManager::remove(IEntity *entity)
{
	m_entities.erase(entity);
}

std::unordered_set<IEntity *> EntityManager::entities() const
{
	return m_entities;
}
