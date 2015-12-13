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
	, m_animatedSpriteState(36)
	, m_collisionHandler(context.m_collisionHandler)
	, m_entityManager(context.m_entityManager)
	, m_direction(0)
	, m_dead(false)
	, m_deathTimer(0)
{
	m_entityManager.add(this);
	m_animatedSpriteState.setSegment(0, 9);
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

	auto animatedSpriteState = m_animatedSpriteState;

	AnimatedSprite sprite(m_texture, animatedSpriteState);
	sprite.setOrigin(sf::Vector2f(32, 32) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	sprite.update(0);

	if (m_direction)
	{
		sprite.setScale(-m_direction, 1);
	}

	if (m_dead)
	{
		const float alpha = std::max(0.0f, (1.0f - (m_deathTimer / 0.5f))) * 255;

		sprite.setColor(sf::Color(255, 255, 255, alpha));
	}

	target.draw(sprite);
}

bool Entity::turnProgress(const float delta)
{
	if (m_direction)
	{
		AnimatedSprite sprite(m_texture, m_animatedSpriteState);
		sprite.update(delta);

		handleMove(delta, m_direction);
	}

	return true;
}

bool Entity::turnEnd(const float delta)
{
	if (m_dead)
	{
		move(0, -delta * 184);

		if ((m_deathTimer += delta) > 0.8f)
		{
			m_entityManager.remove(this);

			return true;
		}

		return false;
	}

	if (isCollidable(0, 1))
	{
		const auto &position = getPosition();
		const auto rx = round(position.x / 32.0f);
		const auto ry = round(position.y / 32.0f);

		setPosition(rx * 32, ry * 32);

		for (Entity *entity : m_entityManager.entities())
		{
			if (entity != this && entity->getPosition() == getPosition())
			{
				entity->kill();
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

void Entity::kill()
{
	m_animatedSpriteState.setSegment(10, 16);
	m_dead = true;
}

bool Entity::isDead() const
{
	return m_dead;
}

bool Entity::isCollidable(int tx, int ty) const
{
	const auto &position = getPosition();
	const auto x = floor(position.x / 32 + .5f);
	const auto y = floor(position.y / 32);

	return m_collisionHandler.isCollidable(x + tx , y + ty);
}
