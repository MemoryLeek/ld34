#include "StateCreationContext.h"

StateCreationContext::StateCreationContext(StateHandler &stateHandler, sf::RenderWindow &window)
	: m_stateHandler(stateHandler)
	, m_window(window)
{

}

StateCreationContext::operator StateHandler &() const
{
	return m_stateHandler;
}

StateCreationContext::operator sf::RenderWindow &() const
{
	return m_window;
}
