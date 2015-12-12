#ifndef ENTITYCREATIONCONTEXT_H
#define ENTITYCREATIONCONTEXT_H

#include <SFML/Graphics/Texture.hpp>

class CollisionHandler;
class EntityManager;

class EntityCreationContext
{
	friend class Entity;

	public:
		EntityCreationContext(const sf::Texture& diffuseTexture, const sf::Texture& normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager);

	private:
		const sf::Texture &m_diffuseTexture;
		const sf::Texture &m_normalTexture;

		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;
};

#endif // ENTITYCREATIONCONTEXT_H
