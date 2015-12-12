#include "EntityCreationContext.h"

EntityCreationContext::EntityCreationContext(const sf::Texture &diffuseTexture, const sf::Texture &normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager)
	: m_diffuseTexture(diffuseTexture)
	, m_normalTexture(normalTexture)
	, m_collisionHandler(collisionHandler)
	, m_entityManager(entityManager)
{

}
