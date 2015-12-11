#include <SFML/Graphics/Sprite.hpp>

#include "TestState.h"
#include "Util.h"

TestState::TestState(sf::RenderWindow& window)
	: m_window(window)
	, m_mouseLight(512, m_normalMapFbo.getTexture(), sf::Color::White)
	, m_testEntity(m_testEntityDiffuse, m_testEntityNormal)
	, m_map("maps/1.json")
{
	m_lightBuffer.create(window.getSize().x, window.getSize().y);
	m_normalMapFbo.create(window.getSize().x, window.getSize().y);

	m_testEntityDiffuse.loadFromFile("sprites/cube.png");
	m_testEntityNormal.loadFromFile("sprites/cube_n.png");
	m_testEntity.setPosition(16 * 50, 16 * 10);
}

void TestState::update(const sf::Time &delta)
{
	m_testEntity.rotate(delta.asSeconds() * 200);
}

void TestState::mouseMoveEvent(const sf::Event& event)
{
	m_mouseWindowPosition.x = event.mouseMove.x;
	m_mouseWindowPosition.y = event.mouseMove.y;
	m_mouseWorldPosition = m_window.mapPixelToCoords(m_mouseWindowPosition);

	m_mouseLight.setPosition(m_mouseWorldPosition);
}

void TestState::mouseScrollEvent(const sf::Event& event)
{
	if (event.mouseWheel.x > 0)
	{
		m_mouseLight.setHeight(m_mouseLight.height() - 0.05f);
	}
	else
	{
		m_mouseLight.setHeight(m_mouseLight.height() + 0.05f);
	}
}

void TestState::keyDownEvent(const sf::Event& event)
{
	UNUSED(event);
}

void TestState::keyUpEvent(const sf::Event& event)
{
	UNUSED(event);
}

void TestState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
		// Step 0 - Draw the map normals to the normal map FBO
	m_normalMapFbo.clear(sf::Color(127, 127, 255)); // Make the empty background face us
	m_map.drawBackgroundNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
	m_testEntity.drawNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
	m_normalMapFbo.display();

	// Step 1 - Draw everything that should receive light
	target.draw(m_map);
	target.draw(m_testEntity);

	// Step 2 - Draw all lights to the light buffer
	m_lightBuffer.clear(sf::Color(100, 100, 100)); // Ambient color
	// Draw all lights (BlendAdd) to the light buffer
	m_lightBuffer.draw(m_mouseLight);
	m_lightBuffer.display();

	// Step 3 - Draw the light buffer to the screen with BlendMultiply
	sf::Sprite lightMapSprite(m_lightBuffer.getTexture());
	target.draw(lightMapSprite, sf::BlendMultiply);

	// Step 4 - Draw everything that doesn't receive light
}

