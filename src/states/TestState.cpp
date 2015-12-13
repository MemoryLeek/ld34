#include <iostream>

#include <SFML/Audio/Listener.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "AnimatedSprite.h"
#include "StateCreationContext.h"
#include "TestState.h"
#include "Util.h"

TestState::TestState(StateCreationContext &context)
	: m_window(context.m_window)
	, m_view(sf::Vector2f(0, 0), sf::Vector2f(m_window.getSize()))
	, m_mapSelectionContext(context.m_mapSelectionContext)
	, m_entityCreationContext(m_collisionHandler, m_entityManager, m_playerState, m_soundEffectPlayer)
	, m_statusIndicators(m_tntTexture, m_snowflakeTexture)
	, m_deathText("YOU ARE DEAD", "Press any key to restart")
	, m_victoryText("STAGE CLEARED", "Press any key to proceed")
	, m_map(m_mapSelectionContext.current(), m_lightContext)
	, m_lightContext(m_map, m_normalMapFbo.getTexture(), m_entityManager)
	, m_mouseLight(m_lightContext, 512, sf::Color::White)
	, m_collisionHandler(m_map)
	, m_turnHandler(m_entityManager)
	, m_stateHandler(context.m_stateHandler)
	, m_fpsCounter(0)
{
	m_lightBuffer.create(m_window.getSize().x, m_window.getSize().y);
	m_normalMapFbo.create(m_window.getSize().x, m_window.getSize().y);

	m_hourGlassTexture.loadFromFile("sprites/hourglass.png");
	m_hourGlassSprite.setTexture(m_hourGlassTexture);
	m_hourGlassSprite.setOrigin(sf::Vector2f(m_hourGlassTexture.getSize()) / 2.f);
	m_hourGlassSprite.setPosition(m_window.getSize().x / 2.f, 64);

	m_testEntityDiffuse.loadFromFile("sprites/cube.png");

	m_wormAnimationStrip.loadFromFile("sprites/worm.png");

	m_tntTexture.loadFromFile("sprites/bomb.png");
	m_snowflakeTexture.loadFromFile("sprites/snowflake.png");

	for (const auto& spawnPoint : m_map.spawnPoints())
	{
		Enemy *enemy = new Enemy(m_wormAnimationStrip, m_playerCharacters, m_entityCreationContext);
		enemy->setPosition(sf::Vector2f(spawnPoint));
	}

	for (const auto& spawnPoint : m_map.playerSpawnPoints())
	{
		auto* player = new PlayerCharacter(m_testEntityDiffuse, m_statusIndicators, m_playerCharacters, m_entityCreationContext);
		player->setPosition(sf::Vector2f(spawnPoint));
		m_playerCharacters.push_back(std::move(player));
	}
}

void TestState::update(const float delta)
{
	m_turnHandler.update(delta);

	// Center the view on the player character that is furthest down
	int y = 0;
	auto characterIterator = m_playerCharacters.begin();
	while (characterIterator != m_playerCharacters.end())
	{
		if ((*characterIterator)->isDead())
		{
			characterIterator = m_playerCharacters.erase(characterIterator++);
		}
		else
		{
			if ((*characterIterator)->getPosition().y > y)
			{
				y = (*characterIterator)->getPosition().y;
			}
			++characterIterator;
		}
	}
	if (y)
	{
		y += 32 * 5;
		if (y < 360)
		{
			y = 360;
		}
		m_view.setCenter(m_window.getSize().x / 2, y);
		sf::Listener::setPosition(m_window.getSize().x / 2, y, 0.f);
	}

	m_fpsTimer += delta;

	if (m_playerCharacters.size() == 0)
	{
		m_deathText.update(delta);
	}

	if (m_playerState.isGoalReached())
	{
		m_victoryText.update(delta);
	}
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
	if (m_playerState.isGoalReached())
	{
		if (!m_stateHandler.isChangingState())
		{
			m_mapSelectionContext.nextMap();

			m_stateHandler.changeState<TestState>(true);
		}

		return;
	}

	if (m_playerCharacters.size() == 0)
	{
		m_stateHandler.changeState<TestState>(true);

		return;
	}

	switch (event.key.code)
	{
		case sf::Keyboard::D:
		{
			if (!m_turnHandler.isRunning())
			{
				for (auto& character : m_playerCharacters)
				{
					character->setDirection(1);
				}
				m_turnHandler.execute();
			}

			return;
		}

		case sf::Keyboard::A:
		{
			if (!m_turnHandler.isRunning())
			{
				for (auto& character : m_playerCharacters)
				{
					character->setDirection(-1);
				}
				m_turnHandler.execute();
			}

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
	UNUSED(event);
}

void TestState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	target.setView(m_view);

	// Step 0 - Draw the map normals to the normal map FBO
	m_normalMapFbo.clear(sf::Color(127, 127, 255)); // Make the empty background face us
	m_map.drawBackgroundNormalMapTo(m_normalMapFbo, sf::BlendAlpha);

	const auto &entities = m_entityManager.entities();

//	for (const auto* entity : entities)
//	{
//		entity->drawNormalMapTo(m_normalMapFbo, sf::BlendAlpha);
//	}
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
//	target.draw(m_testWorm);

	m_fpsCounter++;
	if (m_fpsTimer >= 1)
	{
		std::cout << "FPS: " << m_fpsCounter << std::endl;
		m_fpsCounter = 0;
		m_fpsTimer = 0;
	}

	target.draw(m_deathText);
	target.draw(m_victoryText);
	if (m_turnHandler.isRunning())
	{
		target.draw(m_hourGlassSprite);
	}
	target.setView(m_view);
}

