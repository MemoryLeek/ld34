#include "MenuState.h"
#include "TestState.h"
#include "StateCreationContext.h"
#include "StateHandler.h"
#include "Util.h"

MenuState::MenuState(StateCreationContext &context)
	: m_stateHandler(context.m_stateHandler)
{

}

void MenuState::update(const float delta)
{
	UNUSED(delta);
}

void MenuState::mouseMoveEvent(const sf::Event &event)
{
	UNUSED(event);
}

void MenuState::mouseScrollEvent(const sf::Event &event)
{
	UNUSED(event);
}

void MenuState::keyPressedEvent(const sf::Event &event)
{
	UNUSED(event);
}

void MenuState::keyReleasedEvent(const sf::Event &event)
{
	UNUSED(event);
}

void MenuState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(target);
	UNUSED(states);
}
