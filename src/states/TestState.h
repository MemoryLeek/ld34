#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "CollisionHandler.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include "EntityCreationContext.h"
#include "IState.h"
#include "Light.h"
#include "TurnHandler.h"
#include "Enemy.h"
#include "ITextureProvider.h"
#include "StateHandler.h"
#include "StatusIndicators.h"
#include "SoundEffectPlayer.h"
#include "TextOverlay.h"
#include "PlayerStateManager.h"

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

		mutable sf::RenderTexture m_lightBuffer;
		mutable sf::RenderTexture m_normalMapFbo;

		PlayerCharacterTextureProvider m_playerCharacterTextureProvider;
		EnemyTextureProvider m_enemyTextureProvider;
		MapSelectionContext &m_mapSelectionContext;

		SoundEffectPlayer m_soundEffectPlayer;
		EntityManager m_entityManager;
		PlayerState m_playerState;
		EntityCreationContext m_entityCreationContext;
		std::vector<PlayerCharacter*> m_playerCharacters;

		sf::Texture m_hourGlassTexture;
		sf::Sprite m_hourGlassSprite;

		sf::Texture m_testEntityDiffuse;
		sf::Texture m_wormAnimationStrip;
		sf::Texture m_tntTexture;
		sf::Texture m_snowflakeTexture;
		StatusIndicators m_statusIndicators;

		TextOverlay m_deathText;
		TextOverlay m_victoryText;

		Tiled::Map m_map;
		LightContext m_lightContext;
		CollisionHandler m_collisionHandler;
		TurnHandler m_turnHandler;
		StateHandler &m_stateHandler;

//		mutable float m_fpsTimer;

//		mutable int m_fpsCounter;
};

#endif // TESTSTATE_H
