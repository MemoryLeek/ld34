#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CollisionHandler.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Util.h"

Entity::Entity(const sf::Texture &diffuseTexture, const sf::Texture &normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager)
	: m_diffuseTexture(diffuseTexture)
	, m_normalTexture(normalTexture)
	, m_collisionHandler(collisionHandler)
	, m_entityManager(entityManager)
	, m_direction(0)
	, m_pending(0)
	, m_remaining(0)
{
	entityManager.add(this);

	m_normalMapRotationShader.loadFromFile("glsl/passthrough.vert", "glsl/normalmaprotation.frag");
	m_normalMapRotationShader.setParameter("texture", m_normalTexture);
}

Entity::~Entity()
{
	m_entityManager.remove(this);
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
	if (m_remaining > 0)
	{
		const auto remainingDelta = (m_remaining - delta < 0) ? m_remaining : delta;

		move(m_direction * (remainingDelta * 128), 0);
		rotate(m_direction * (remainingDelta * 360));

		m_remaining -= delta;
	}
	else
	{
		m_direction = m_pending;

		if (isCollidable(0, 1))
		{
			const auto &position = getPosition();
			const auto rx = round(position.x / 32.0f);
			const auto ry = round(position.y / 32.0f);

			setPosition(rx * 32, position.y);
			setPosition(rx * 32, ry * 32);
		}
		else
		{
			move(0, delta * 184);
		}
	}
}

void Entity::setDirection(int direction)
{
	if (direction)
	{
		if (isCollidable(0, 1) &&
			isCollidable(direction, 0) == false)
		{
			if (!m_direction)
			{
				m_pending = direction;
				m_remaining = 0.25f;
			}
		}
	}
	else
	{
		m_pending = 0;
	}
}

void Entity::execute()
{
	if (!m_direction)
	{
		m_direction = m_pending;
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

bool Entity::isCollidable(int tx, int ty) const
{
	const sf::Vector2f &position = getPosition();

	const int x = floor(position.x / 32);
	const int y = floor(position.y / 32);

	return m_collisionHandler.isCollidable(x + tx , y + ty);
}
