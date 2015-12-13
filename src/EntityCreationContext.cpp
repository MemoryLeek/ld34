#include "EntityCreationContext.h"

EntityCreationContext::EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager, PlayerState &playerStateManager, SoundEffectPlayer &soundEffectPlayer)
	: m_collisionHandler(collisionHandler)
	, m_entityManager(entityManager)
	, m_playerState(playerStateManager)
	, m_soundEffectPlayer(soundEffectPlayer)
{

}
