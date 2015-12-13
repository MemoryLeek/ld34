#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "AnimatedSprite.h"
#include "AnimatedSpriteState.h"
#include "ITurn.h"
#include "IEntity.h"

namespace Tiled
{
	class Map;
}
class CollisionHandler;
class EntityCreationContext;
class EntityManager;
class ITextureProvider;
class ISpriteSegmentDefinition;

class Character : public IEntity
{
	const sf::Vector2f Offset = sf::Vector2f(16, 12);

	public:
		Character(const sf::Texture &texture, const EntityCreationContext &context);
		~Character();

		int direction() const;
		void setDirection(int direction);

		bool turnProgress(const float delta) override;
		bool turnEnd(const float delta) override;

		void setIsDead(bool isDead);
		bool isDead() const;

	protected:
		enum PowerUp
		{
			Neutral = 1,
			Growing = 2,
			Explosive = 3,
			Frozen = 4
		};

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		int getTileType(int tx, int ty) const;

		const sf::Texture &m_texture;
		const EntityCreationContext &m_creationContext;
		EntityManager &m_entityManager;

	private:
		AnimatedSpriteState m_animatedSpriteState;
		CollisionHandler &m_collisionHandler;

		int m_direction;

		bool m_dead;

		float m_deathTimer;
};

#endif // CHARACTER_H
