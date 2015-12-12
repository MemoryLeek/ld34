#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Light.h"
#include "tiled/Map.h"

Light::Light(float radius, const Tiled::Map& map, const sf::Texture &screenSpaceNormalMap, const std::vector<Entity *> &shadowCastingEntities, const sf::Color &color)
	: m_radius(radius)
	, m_map(map)
	, m_screenSpaceNormalMap(screenSpaceNormalMap)
	, m_shadowCastingEntities(shadowCastingEntities)
	, m_color(color)
	, m_height(.1f)
{
	setOrigin(radius, radius);

	m_shadowMapShader.loadFromFile("glsl/passthrough.vert", "glsl/shadowmap.frag");
	m_lightMapShader.loadFromFile("glsl/passthrough.vert", "glsl/lightsource.frag");

	m_shadowMapRect.resize(4);
	m_shadowMapRect.setPrimitiveType(sf::Quads);
	m_shadowMapRect[0].position = sf::Vector2f(0, 0);
	m_shadowMapRect[1].position = sf::Vector2f(radius * 2, 0);
	m_shadowMapRect[2].position = sf::Vector2f(radius * 2, 1);
	m_shadowMapRect[3].position = sf::Vector2f(0, 1);
	m_shadowMapRect[0].texCoords = sf::Vector2f(0, 0);
	m_shadowMapRect[1].texCoords = sf::Vector2f(1, 0);
	m_shadowMapRect[2].texCoords = sf::Vector2f(1, 1);
	m_shadowMapRect[3].texCoords = sf::Vector2f(0, 1);

	m_occlusionMapRect = m_shadowMapRect;
	m_occlusionMapRect[0].position = sf::Vector2f(0, 0);
	m_occlusionMapRect[1].position = sf::Vector2f(radius * 2, 0);
	m_occlusionMapRect[2].position = sf::Vector2f(radius * 2, radius * 2);
	m_occlusionMapRect[3].position = sf::Vector2f(0, radius * 2);
	m_occlusionMapRect[0].color = sf::Color::White;
	m_occlusionMapRect[1].color = sf::Color::White;
	m_occlusionMapRect[2].color = sf::Color::White;
	m_occlusionMapRect[3].color = sf::Color::White;

	m_normalMap.create(radius * 2, radius * 2);
	m_occlusionMap.create(radius * 2, radius * 2);
	m_occlusionMap.setSmooth(true);
	m_shadowMap.create(radius * 2, 1);
	m_shadowMap.setSmooth(true);

	m_shadowMapShader.setParameter("resolution", sf::Vector2f(m_occlusionMap.getSize()));
	m_shadowMapShader.setParameter("texture", m_occlusionMap.getTexture());

	m_lightMapShader.setParameter("resolution", sf::Vector2f(m_occlusionMap.getSize()));
	m_lightMapShader.setParameter("texture", m_shadowMap.getTexture());
	m_lightMapShader.setParameter("normalmap", m_normalMap.getTexture());
	m_lightMapShader.setParameter("lightColor", color);
	m_lightMapShader.setParameter("lightHeight", m_height);
}

float Light::height() const
{
	return m_height;
}

Light& Light::setHeight(float height)
{
	m_height = (height < 0.05f) ? 0.05f : (height > 1) ? 1 : height;
	m_lightMapShader.setParameter("lightHeight", m_height);
	return *this;
}

void Light::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	#if 0 // Debug light outline drawing
	sf::CircleShape circle(m_radius);
	circle.setPosition(getPosition() - getOrigin());
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1);
	target.draw(circle, states);
	#endif

	sf::View lightView;
	lightView.setCenter(getPosition().x, getPosition().y);
	lightView.setSize(m_radius * 2, m_radius * 2);

	// Create an occlusion map with all objects that cast shadows
	m_occlusionMap.setView(lightView);
	m_occlusionMap.clear(sf::Color::Transparent);
	for (const auto& layer : m_map.layers())
	{
		if (layer.property("castShadows"))
		{
			m_occlusionMap.draw(layer);
		}
	}
	for (const auto* occluder : m_shadowCastingEntities)
	{
		m_occlusionMap.draw(*occluder);
	}
	m_occlusionMap.display();

	// Create a shadow map from our occlusion map
	m_shadowMap.clear(sf::Color::Transparent);
	m_shadowMap.draw(m_shadowMapRect, &m_shadowMapShader);
	m_shadowMap.display();

	// Draw from the screen space normal map to the lights normal map
	sf::Sprite ssnm(m_screenSpaceNormalMap, sf::IntRect(getPosition().x - m_radius, getPosition().y - m_radius, lightView.getSize().x, lightView.getSize().y));
	m_normalMap.draw(ssnm);
	m_normalMap.display();

	// Draw the light from the shadow map, re-use the occlusion map FBO
	m_occlusionMap.setView(m_occlusionMap.getDefaultView());
	m_occlusionMap.clear(sf::Color::Transparent);
	m_occlusionMap.draw(m_occlusionMapRect, &m_lightMapShader);
	m_occlusionMap.display();

	// Draw the light
	sf::Sprite lightMapSprite(m_occlusionMap.getTexture());
	lightMapSprite.setOrigin(m_radius, m_radius);
	lightMapSprite.setPosition(getPosition());
	target.draw(lightMapSprite, sf::BlendAdd);
}
