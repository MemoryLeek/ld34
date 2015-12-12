#include "EntityManager.h"

void EntityManager::add(Entity *entity)
{
	m_entities.insert(entity);
}

void EntityManager::remove(Entity *entity)
{
	m_entities.erase(entity);
}

std::unordered_set<Entity *> EntityManager::entities() const
{
	return m_entities;
}
