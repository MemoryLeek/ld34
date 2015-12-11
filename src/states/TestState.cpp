#include <SFML/Graphics/Sprite.hpp>

#include "StateCreationContext.h"
#include "TestState.h"
#include "Util.h"

TestState::TestState(StateCreationContext &context)
	: m_window(context)
	, m_mouseLight(512, m_normalMapFbo.getTexture(), m_entities, sf::Color::White)
	, m_testEntity(m_testEntityDiffuse, m_testEntityNormal, m_collisionHandler)
	, m_map("maps/1.json")
	, m_collisionHandler(m_map)
{
	sf::View view(sf::FloatRect(0, 0, 640, 360));

	m_window.setView(view);

	m_lightBuffer.create(m_window.getSize().x, m_window.getSize().y);
	m_normalMapFbo.create(m_window.getSize().x, m_window.getSize().y);

	m_testEntityDiffuse.loadFromFile("sprites/cube.png");
	m_testEntityNormal.loadFromFile("sprites/cube_n.png");
	m_testEntity.setPosition(16 * 10, 16 * 9);

	m_entities.push_back(&m_testEntity);
}

void TestState::update(const float delta)
{
	m_testEntity.update(delta);
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

void TestState::keyPressedEvent(const sf::Event& event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::D:
		{
			return m_testEntity.setDirection(1);
		}

		case sf::Keyboard::A:
		{
			return m_testEntity.setDirection(-1);
		}

		default:
		{
			return;
		}
	}
}

void TestState::keyReleasedEvent(const sf::Event& event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::D:
		case sf::Keyboard::A:
		{
			return m_testEntity.setDirection(0);
		}

		default:
		{
			return;
		}
	}
}

void TestState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Step 0 - Draw the map normals to the normal map FBO
	m_normalMapFbo.clear(sf::Color(127, 127, 255)); // Make the empty background face us
	m_map.drawBackgroundNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
	for (const auto* entity : m_entities)
	{
		entity->drawNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
	}
	m_normalMapFbo.display();

	// Step 1 - Draw everything that should receive light
	target.draw(m_map);
	for (const auto* entity : m_entities)
	{
		target.draw(*entity);
	}

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

