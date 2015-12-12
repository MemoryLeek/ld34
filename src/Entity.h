#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

class CollisionHandler;
class EntityManager;

class Entity : public sf::Drawable, public sf::Transformable
{
	const sf::Vector2f Offset = sf::Vector2f(16, 12);

	public:
		Entity(const sf::Texture& diffuseTexture, const sf::Texture& normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager);
		~Entity();

		void drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;
		void update(float delta);

		void setDirection(int direction);
		void execute();

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		bool isCollidable(int tx, int ty) const;

		const sf::Texture& m_diffuseTexture;
		const sf::Texture& m_normalTexture;

		CollisionHandler &m_collisionHandler;
		EntityManager &m_entityManager;

		mutable sf::Shader m_normalMapRotationShader;

		int m_direction;
		int m_pending;

		float m_remaining;
};

#endif // ENTITY_H
