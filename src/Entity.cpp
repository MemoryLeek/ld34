#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CollisionHandler.h"
#include "Entity.h"
#include "Util.h"

Entity::Entity(const sf::Texture &diffuseTexture, const sf::Texture &normalTexture, const CollisionHandler &collisionHandler)
	: m_diffuseTexture(diffuseTexture)
	, m_normalTexture(normalTexture)
	, m_collisionHandler(collisionHandler)
	, m_direction(0)
	, m_pending(0)
	, m_remaining(0)
{
	m_normalMapRotationShader.loadFromFile("glsl/passthrough.vert", "glsl/normalmaprotation.frag");
	m_normalMapRotationShader.setParameter("texture", m_normalTexture);
}

void Entity::drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const
{
	m_normalMapRotationShader.setParameter("rotation", (getRotation() * M_PI / 180));

	sf::Sprite sprite(m_normalTexture);
	sprite.setOrigin(sf::Vector2f(m_normalTexture.getSize()) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	target.draw(sprite, &m_normalMapRotationShader);
}

void Entity::update(float delta)
{
	if ((m_remaining -= delta) > 0)
	{
		move(m_direction * (delta * 32), 0);
		rotate(m_direction * (delta * 180));
	}
	else
	{
		m_direction = m_pending;

		if (!isOnGround())
		{
			move(0, delta * 92);
		}
	}
}

void Entity::setDirection(int direction)
{
	if (direction)
	{
		if (isOnGround() && !m_direction)
		{
			m_direction = direction;
			m_pending = direction;
			m_remaining = 0.5f;
		}
	}
	else
	{
		m_pending = 0;
	}
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	sf::Sprite sprite(m_diffuseTexture);
	sprite.setOrigin(sf::Vector2f(m_diffuseTexture.getSize()) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	target.draw(sprite);
}

bool Entity::isOnGround() const
{
	const sf::Vector2f &position = getPosition();

	const int x = floor(position.x / 16);
	const int y = floor(position.y / 16);

	return m_collisionHandler.isCollidable(x, y + 1);
}

