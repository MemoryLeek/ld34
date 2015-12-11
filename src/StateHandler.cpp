#include "StateHandler.h"

StateHandler::StateHandler(sf::RenderWindow& window)
	: m_state(window)
{

}

IState& StateHandler::currentState()
{
	return m_state;
}
