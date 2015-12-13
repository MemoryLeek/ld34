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
class SoundEffectPlayer;

class EntityCreationContext
{
	friend class Character;

	public:
		EntityCreationContext(CollisionHandler &collisionHandler, EntityManager &entityManager, PlayerState &playerStateManager, SoundEffectPlayer &soundEffectPlayer);

	private:
		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;
		PlayerState &m_playerState;
		SoundEffectPlayer &m_soundEffectPlayer;
};

#endif // ENTITYCREATIONCONTEXT_H
