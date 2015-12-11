#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

class IState;

class Window
{
	public:
		Window();

		void run();

	private:
		void routeEvent(const sf::Event& event, sf::RenderWindow& window, IState& state);
};

#endif // WINDOW_H
