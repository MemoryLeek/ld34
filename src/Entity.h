#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "AnimatedSprite.h"
#include "ITurn.h"

class CollisionHandler;
class EntityCreationContext;
class EntityManager;
class ITextureProvider;

class Entity
	: public sf::Drawable
	, public sf::Transformable
	, public ITurn
{
	const sf::Vector2f Offset = sf::Vector2f(16, 12);

	public:
		Entity(const sf::Texture &texture, const EntityCreationContext &context);
		~Entity();

		int direction() const;
		void setDirection(int direction);

		bool turnProgress(const float delta) override;
		bool turnEnd(const float delta) override;

	protected:
		virtual void handleMove(const float delta, const int direction) = 0;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		bool isCollidable(int tx, int ty) const;

	private:
		const sf::Texture &m_texture;

		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;

		int m_currentFrame;
		int m_direction;
};

#endif // ENTITY_H
