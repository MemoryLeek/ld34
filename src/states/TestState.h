#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "CollisionHandler.h"
#include "Entity.h"
#include "IState.h"
#include "Light.h"

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

		sf::Vector2i m_mouseWindowPosition;
		sf::Vector2f m_mouseWorldPosition;

		mutable sf::RenderTexture m_lightBuffer;
		mutable sf::RenderTexture m_normalMapFbo;

		Entity m_testEntity;

		std::vector<Entity*> m_entities;

		sf::Texture m_testEntityDiffuse;
		sf::Texture m_testEntityNormal;

		Tiled::Map m_map;
		LightContext m_lightContext;
		Light m_mouseLight;
		CollisionHandler m_collisionHandler;

		mutable float m_fpsTimer;
		mutable int m_fpsCounter;
};

#endif // TESTSTATE_H
