#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.h"

Entity::Entity(const sf::Texture &diffuseTexture, const sf::Texture &normalTexture)
	: m_diffuseTexture(diffuseTexture)
	, m_normalTexture(normalTexture)
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
	sprite.setPosition(getPosition());
	target.draw(sprite, &m_normalMapRotationShader);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Sprite sprite(m_diffuseTexture);
	sprite.setOrigin(sf::Vector2f(m_diffuseTexture.getSize()) / 2.f);
	sprite.setRotation(getRotation());
	sprite.setPosition(getPosition());
	target.draw(sprite);
}

