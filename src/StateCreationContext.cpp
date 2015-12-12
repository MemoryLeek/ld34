#include "StateCreationContext.h"

StateCreationContext::StateCreationContext(StateHandler &stateHandler, sf::RenderWindow &window)
	: m_stateHandler(stateHandler)
	, m_window(window)
{

}
