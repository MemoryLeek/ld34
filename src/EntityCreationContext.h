#ifndef ENTITYCREATIONCONTEXT_H
#define ENTITYCREATIONCONTEXT_H

#include <SFML/Graphics/Texture.hpp>

namespace Tiled
{
	class Map;
}
class CollisionHandler;
class EntityManager;

class EntityCreationContext
{
	friend class Character;

	public:
		EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager);

	private:
		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;
};

#endif // ENTITYCREATIONCONTEXT_H
