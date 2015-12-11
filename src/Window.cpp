#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "StateHandler.h"
#include "Window.h"

Window::Window()
{

}

void Window::run()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld34");
	sf::Event event;

	StateHandler stateHandler(window);

	while (window.isOpen())
	{
		IState& state = stateHandler.currentState();

		while (window.pollEvent(event))
		{
			routeEvent(event, window, state);
		}

		window.clear(sf::Color::White);

		state.draw();

		window.display();
	}
}

void Window::routeEvent(const sf::Event& event, sf::RenderWindow& window, IState& state)
{
	switch (event.type)
	{
		case sf::Event::Closed:
		{
			return window.close();
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

