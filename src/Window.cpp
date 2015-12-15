#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "StateCreationContext.h"
#include "StateHandler.h"
#include "Window.h"
#include "IState.h"

Window::Window()
{

}

void Window::run()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Kubble");
	window.setKeyRepeatEnabled(false);

	sf::Clock deltaTimer;
	sf::Event event;

	sf::Music music;
	music.openFromFile("music/ld34.ogg");
	music.setVolume(80);
	music.setLoop(true);
	music.play();

	StateHandler stateHandler(window);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			routeEvent(event, window, stateHandler);
		}

		const float delta = deltaTimer
			.restart()
			.asSeconds();

		stateHandler.update(delta);

		window.clear(sf::Color::White);
		window.draw(stateHandler);
		window.display();
	}
}

void Window::routeEvent(const sf::Event& event, sf::RenderWindow& window, StateHandler& stateHandler)
{
	IState &state = stateHandler.currentState();

	switch (event.type)
	{
		case sf::Event::Closed:
		{
			return window.close();
		}

		case sf::Event::KeyPressed:
		{
			return state.keyPressedEvent(event);
		}

		case sf::Event::KeyReleased:
		{
			return state.keyReleasedEvent(event);
		}

		case sf::Event::MouseMoved:
		{
			return state.mouseMoveEvent(event);
		}

		case sf::Event::MouseWheelScrolled:
		{
			return state.mouseScrollEvent(event);
		}

		default:
		{
			return;
		}
	}
}

