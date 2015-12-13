#ifndef STATECREATIONCONTEXT_H
#define STATECREATIONCONTEXT_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "MapSelectionContext.h"

class StateHandler;

class StateCreationContext
{
	friend class LogoState;
	friend class TestState;
	friend class MenuState;

	public:
		StateCreationContext(StateHandler &stateHandler, MapSelectionContext &mapSelectionContext, sf::RenderWindow &window);

	private:
		StateHandler &m_stateHandler;
		MapSelectionContext &m_mapSelectionContext;

		sf::RenderWindow &m_window;
};

#endif // STATECREATIONCONTEXT_H
