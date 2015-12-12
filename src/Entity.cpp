#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ITextureProvider.h"
#include "CollisionHandler.h"
#include "EntityCreationContext.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Util.h"

Entity::Entity(const sf::Texture &texture, const EntityCreationContext &context)
	: m_texture(texture)
	, m_collisionHandler(context.m_collisionHandler)
	, m_entityManager(context.m_entityManager)
	, m_currentFrame(0)
	, m_direction(0)
{
	m_entityManager.add(this);
}

Entity::~Entity()
{
	m_entityManager.remove(this);
}

int Entity::direction() const
{
	return m_direction;
}

void Entity::setDirection(int direction)
{
	if (isCollidable(0, 1) >
		isCollidable(direction, 0))
	{
		m_direction = direction;
	}
	else
	{
		m_direction = 0;
	}

	if (m_collisionHandler.getTriggers(getPosition()).size() > 0)
	{
//		std::cout << "Inside triggers" << std::endl;
	}
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	int currentFrame = m_currentFrame;

	AnimatedSprite sprite(m_texture, 36, currentFrame);
	sprite.setOrigin(sf::Vector2f(32, 32) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	sprite.update(0);

	if (m_direction)
	{
		sprite.setScale(-m_direction, 1);
	}

	target.draw(sprite);
}

bool Entity::turnProgress(const float delta)
{
	if (m_direction)
	{
		AnimatedSprite sprite(m_texture, 36, m_currentFrame);
		sprite.update(delta);

		handleMove(delta, m_direction);
	}

	return true;
}

bool Entity::turnEnd(const float delta)
{
	if (isCollidable(0, 1))
	{
		const auto &position = getPosition();
		const auto rx = round(position.x / 32.0f);
		const auto ry = round(position.y / 32.0f);

		setPosition(rx * 32, ry * 32);

		for (const auto& entity : m_entityManager.entities())
		{
			if (entity != this && entity->getPosition() == getPosition())
			{
				std::cout << "Inside entity, kill it with fire" << std::endl;
			}
		}

		return true;
	}
	else
	{
		move(0, delta * 184);
	}

	return false;
}

bool Entity::isCollidable(int tx, int ty) const
{
	const auto &position = getPosition();
	const auto x = floor(position.x / 32 + .5f);
	const auto y = floor(position.y / 32);

	return m_collisionHandler.isCollidable(x + tx , y + ty);
}
