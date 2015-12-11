#ifndef ISTATE
#define ISTATE

#include <SFML/Window/Event.hpp>

class IState
{
	public:
		virtual void draw() = 0;

		virtual void mouseMoveEvent(const sf::Event &event) = 0;
		virtual void mouseScrollEvent(const sf::Event &event) = 0;

		virtual void keyDownEvent(const sf::Event &event) = 0;
		virtual void keyUpEvent(const sf::Event &event) = 0;
};

#endif // ISTATE

