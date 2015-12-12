#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

#include "StateCreationContext.h"
#include "TestState.h"
#include "Util.h"

TestState::TestState(StateCreationContext &context)
	: m_window(context.m_window)
	, m_view(sf::Vector2f(0, 0), sf::Vector2f(m_window.getSize()))
	, m_entityCreationContext(m_testEntityDiffuse, m_testEntityNormal, m_collisionHandler, m_entityManager)
	, m_testEntity(m_playerCharacterTextureProvider, m_entityCreationContext)
	, m_enemy(m_enemyTextureProvider, m_entityCreationContext)
	, m_map("maps/1.json", m_lightContext)
	, m_lightContext(m_map, m_normalMapFbo.getTexture(), m_entityManager)
	, m_mouseLight(m_lightContext, 512, sf::Color::White)
	, m_collisionHandler(m_map)
	, m_turnHandler(m_entityManager)
	, m_fpsCounter(0)
{
	m_lightBuffer.create(m_window.getSize().x, m_window.getSize().y);
	m_normalMapFbo.create(m_window.getSize().x, m_window.getSize().y);

	m_testEntityDiffuse.loadFromFile("sprites/cube.png");
	m_testEntityNormal.loadFromFile("sprites/cube_n.png");
	m_testEntity.setPosition(16 * 10, 0);
}

void TestState::update(const float delta)
{
	m_testEntity.update(delta);
	m_enemy.update(delta);

	m_view.setCenter(m_testEntity.getPosition() - sf::Vector2f(0, 32 * -10));

	m_fpsTimer += delta;
}

void TestState::mouseMoveEvent(const sf::Event& event)
{
	m_mouseWindowPosition.x = event.mouseMove.x;
	m_mouseWindowPosition.y = event.mouseMove.y;
	m_mouseWorldPosition = m_window.mapPixelToCoords(m_mouseWindowPosition);

	m_mouseLight.setPosition(sf::Vector2f(sf::Vector2i(m_mouseWorldPosition)));
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
			m_testEntity.setDirection(1);
			m_turnHandler.execute();

			return;
		}

		case sf::Keyboard::A:
		{
			m_testEntity.setDirection(-1);
			m_turnHandler.execute();

			return;
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
	UNUSED(states);

	target.setView(m_view);

	// Step 0 - Draw the map normals to the normal map FBO
	m_normalMapFbo.clear(sf::Color(127, 127, 255)); // Make the empty background face us
	m_map.drawBackgroundNormalMapTo(m_normalMapFbo, sf::BlendAlpha);

	const auto &entities = m_entityManager.entities();

	for (const auto* entity : entities)
	{
		entity->drawNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
	}
	m_normalMapFbo.display();

	// Step 1 - Draw everything that should receive light
	for (const auto& layer : m_map.layers())
	{
		if (!layer.property("castShadows"))
		{
			target.draw(layer);
		}
	}

	// Step 2 - Draw all lights to the light buffer
	m_lightBuffer.setView(m_view);
	m_lightBuffer.clear(sf::Color(100, 100, 100)); // Ambient color
	// Draw all lights (BlendAdd) to the light buffer
	for (const auto& light : m_map.lights())
	{
		m_lightBuffer.draw(*light);
	}
	m_lightBuffer.draw(m_mouseLight);
	m_lightBuffer.display();

	// Step 3 - Draw the light buffer to the screen with BlendMultiply
	sf::Sprite lightMapSprite(m_lightBuffer.getTexture());
	target.setView(target.getDefaultView());
	target.draw(lightMapSprite, sf::BlendMultiply);
	target.setView(m_view);

	// Step 4 - Draw everything that doesn't receive light
	for (const auto& layer : m_map.layers())
	{
		if (layer.property("castShadows"))
		{
			target.draw(layer);
		}
	}
	for (const auto* entity : entities)
	{
		target.draw(*entity);
	}

	m_fpsCounter++;
	if (m_fpsTimer >= 1)
	{
		std::cout << "FPS: " << m_fpsCounter << std::endl;
		m_fpsCounter = 0;
		m_fpsTimer = 0;
	}
}

