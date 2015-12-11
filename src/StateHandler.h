#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "states/TestState.h"

class IState;

class StateHandler
{
	public:
		StateHandler(sf::RenderWindow& window);

		IState& currentState();

	private:
		TestState m_state;
};

#endif // STATEHANDLER_H
