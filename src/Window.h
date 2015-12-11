#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

class IState;
class StateHandler;

class Window
{
	public:
		Window();

		void run();

	private:
		void routeEvent(const sf::Event& event, sf::RenderWindow& window, StateHandler &stateHandler);
};

#endif // WINDOW_H
