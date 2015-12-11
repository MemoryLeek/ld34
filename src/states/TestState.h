#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "IState.h"
#include "Light.h"

#include "tiled/Map.h"

class TestState : public IState
{
	public:
		TestState(sf::RenderWindow& window);

		void draw() override;

		void mouseMoveEvent(const sf::Event& event) override;
		void mouseScrollEvent(const sf::Event& event) override;

		void keyDownEvent(const sf::Event& event) override;
		void keyUpEvent(const sf::Event& event) override;

	private:
		sf::RenderWindow& m_window;

		sf::Vector2i m_mouseWindowPosition;
		sf::Vector2f m_mouseWorldPosition;

		sf::RenderTexture m_lightBuffer;
		sf::RenderTexture m_normalMapFbo;

		Light m_mouseLight;

		Tiled::Map m_map;
};

#endif // TESTSTATE_H
