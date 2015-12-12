#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimatedSprite.h"
#include "CollisionHandler.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include "EntityCreationContext.h"
#include "IState.h"
#include "Light.h"
#include "TurnHandler.h"
#include "Enemy.h"
#include "ITextureProvider.h"

#include "tiled/Map.h"

class StateHandler;
class StateCreationContext;

class TestState : public IState
{
	public:
		TestState(StateCreationContext &context);

		void update(const float delta) override;

		void mouseMoveEvent(const sf::Event& event) override;
		void mouseScrollEvent(const sf::Event& event) override;

		void keyPressedEvent(const sf::Event& event) override;
		void keyReleasedEvent(const sf::Event& event) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		sf::RenderWindow& m_window;
		sf::View m_view;

		sf::Vector2i m_mouseWindowPosition;
		sf::Vector2f m_mouseWorldPosition;

		mutable sf::RenderTexture m_lightBuffer;
		mutable sf::RenderTexture m_normalMapFbo;

		PlayerCharacterTextureProvider m_playerCharacterTextureProvider;
		EnemyTextureProvider m_enemyTextureProvider;

		EntityManager m_entityManager;
		EntityCreationContext m_entityCreationContext;
		PlayerCharacter m_testEntity;
		Enemy m_enemy;

		sf::Texture m_testEntityDiffuse;
		sf::Texture m_testEntityNormal;

		sf::Texture m_wormAnimationStrip;
		AnimatedSprite m_testWorm;

		Tiled::Map m_map;
		LightContext m_lightContext;
		Light m_mouseLight;
		CollisionHandler m_collisionHandler;
		TurnHandler m_turnHandler;

		mutable float m_fpsTimer;
		mutable int m_fpsCounter;
};

#endif // TESTSTATE_H
