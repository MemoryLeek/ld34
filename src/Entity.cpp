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

Entity::Entity(ITextureProvider &textureProvider, const EntityCreationContext &context)
	: m_textureProvider(textureProvider)
	, m_collisionHandler(context.m_collisionHandler)
	, m_entityManager(context.m_entityManager)
	, m_direction(0)
{
	m_entityManager.add(this);

	const auto &normalTexture = m_textureProvider.normalTexture();

	m_normalMapRotationShader.loadFromFile("glsl/passthrough.vert", "glsl/normalmaprotation.frag");
	m_normalMapRotationShader.setParameter("texture", normalTexture);
}

Entity::~Entity()
{
	m_entityManager.remove(this);
}

void Entity::drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const
{
	m_normalMapRotationShader.setParameter("rotation", (getRotation() * M_PI / 180));

	const auto &normalTexture = m_textureProvider.normalTexture();

	sf::Sprite sprite(normalTexture);
	sprite.setOrigin(sf::Vector2f(normalTexture.getSize()) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	target.draw(sprite, &m_normalMapRotationShader);
}

void Entity::setDirection(int direction)
{
	if (isCollidable(0, 1) && !
		isCollidable(direction, 0))
	{
		m_direction = direction;
	}

	if (m_collisionHandler.getTriggers(getPosition()).size() > 0)
	{
//		std::cout << "Inside triggers" << std::endl;
	}
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const auto &diffuseTexture = m_textureProvider.diffuseTexture();

	sf::Sprite sprite(diffuseTexture);
	sprite.setOrigin(sf::Vector2f(diffuseTexture.getSize()) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition() + Offset);
	target.draw(sprite);
}

void Entity::turnProgress(const float delta)
{
	if (m_direction)
	{
		handleMove(delta, m_direction);
	}
	else
	{
		turnIdle(delta);
	}
}

void Entity::turnIdle(const float delta)
{
	m_direction = 0;

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

bool Entity::isCollidable(int tx, int ty) const
{
	const auto &position = getPosition();
	const auto x = floor(position.x / 32);
	const auto y = floor(position.y / 32);

	return m_collisionHandler.isCollidable(x + tx , y + ty);
}
