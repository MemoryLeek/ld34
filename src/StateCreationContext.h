#ifndef STATECREATIONCONTEXT_H
#define STATECREATIONCONTEXT_H

#include <SFML/Graphics/RenderWindow.hpp>

class StateHandler;

class StateCreationContext
{
	friend class LogoState;
	friend class TestState;
	friend class MenuState;

	public:
		StateCreationContext(StateHandler &stateHandler, sf::RenderWindow &window);

	private:
		StateHandler &m_stateHandler;

		sf::RenderWindow &m_window;
};

#endif // STATECREATIONCONTEXT_H
