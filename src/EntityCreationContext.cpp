#include "EntityCreationContext.h"

EntityCreationContext::EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager)
	: m_collisionHandler(collisionHandler)
	, m_entityManager(entityManager)
{

}
