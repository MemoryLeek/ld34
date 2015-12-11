#ifndef STATECREATIONCONTEXT_H
#define STATECREATIONCONTEXT_H

#include <SFML/Graphics/RenderWindow.hpp>

class StateHandler;

class StateCreationContext
{
	public:
		StateCreationContext(StateHandler &stateHandler, sf::RenderWindow &window);

		operator StateHandler &() const;

		operator sf::RenderWindow &() const;

	private:
		StateHandler &m_stateHandler;

		sf::RenderWindow &m_window;
};

#endif // STATECREATIONCONTEXT_H
