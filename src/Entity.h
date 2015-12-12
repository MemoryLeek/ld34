#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

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
		Entity(ITextureProvider &textureProvider, const EntityCreationContext &context);
		~Entity();

		void drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;
		void setDirection(int direction);

		void turnProgress(const float delta) override;
		void turnIdle(const float delta) override;

	protected:
		virtual void handleMove(const float delta, const int direction) = 0;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		bool isCollidable(int tx, int ty) const;

	private:
		ITextureProvider &m_textureProvider;
		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;

		mutable sf::Shader m_normalMapRotationShader;

		int m_direction;
};

#endif // ENTITY_H
