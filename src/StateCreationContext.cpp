#include "StateCreationContext.h"

StateCreationContext::StateCreationContext(StateHandler &stateHandler, MapSelectionContext &mapSelectionContext, sf::RenderWindow &window)
	: m_stateHandler(stateHandler)
	, m_mapSelectionContext(mapSelectionContext)
	, m_window(window)
{

}
