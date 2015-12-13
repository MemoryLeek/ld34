#ifndef ENTITYCREATIONCONTEXT_H
#define ENTITYCREATIONCONTEXT_H

#include <SFML/Graphics/Texture.hpp>

namespace Tiled
{
	class Map;
}

class CollisionHandler;
class EntityManager;
class PlayerState;

class EntityCreationContext
{
	friend class Character;

	public:
		EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager, PlayerState &playerStateManager);

	private:
		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;
		PlayerState &m_playerState;
};

#endif // ENTITYCREATIONCONTEXT_H
