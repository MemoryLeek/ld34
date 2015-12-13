#include "EntityCreationContext.h"

EntityCreationContext::EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager, PlayerState &playerStateManager)
	: m_collisionHandler(collisionHandler)
	, m_entityManager(entityManager)
	, m_playerState(playerStateManager)
{

}
