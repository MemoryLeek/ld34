#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

class CollisionHandler;

class Entity : public sf::Drawable, public sf::Transformable
{
	const sf::Vector2f Offset = sf::Vector2f(16, 16);

	public:
		Entity(const sf::Texture& diffuseTexture, const sf::Texture& normalTexture, const CollisionHandler &collisionHandler);

		void drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;
		void update(float delta);

		void setDirection(int direction);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		bool isCollidable(int tx, int ty) const;

		const sf::Texture& m_diffuseTexture;
		const sf::Texture& m_normalTexture;

		const CollisionHandler &m_collisionHandler;

		mutable sf::Shader m_normalMapRotationShader;

		int m_direction;
		int m_pending;

		float m_remaining;
};

#endif // ENTITY_H
