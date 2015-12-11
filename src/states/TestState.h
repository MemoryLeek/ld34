#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity.h"
#include "IState.h"
#include "Light.h"

#include "tiled/Map.h"

class TestState : public IState
{
	public:
		TestState(sf::RenderWindow& window);

		void update(const sf::Time& delta) override;

		void mouseMoveEvent(const sf::Event& event) override;
		void mouseScrollEvent(const sf::Event& event) override;

		void keyDownEvent(const sf::Event& event) override;
		void keyUpEvent(const sf::Event& event) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		sf::RenderWindow& m_window;

		sf::Vector2i m_mouseWindowPosition;
		sf::Vector2f m_mouseWorldPosition;

		mutable sf::RenderTexture m_lightBuffer;
		mutable sf::RenderTexture m_normalMapFbo;

		Light m_mouseLight;

		sf::Texture m_testEntityDiffuse;
		sf::Texture m_testEntityNormal;
		Entity m_testEntity;

		Tiled::Map m_map;
};

#endif // TESTSTATE_H
