#include "StateCreationContext.h"
#include "StateHandler.h"
#include "TestState.h"
#include "MainMenuState.h"
#include "LogoState.h"
#include "Util.h"

LogoState::LogoState(StateCreationContext &context)
	: m_stateHandler(context.m_stateHandler)
	, m_window(context.m_window)
{
	m_texture.loadFromFile("images/logo.png");

	const sf::Vector2u &size = m_window.getSize();

	const float x = (size.x - 500) / 2;
	const float y = (size.y - 295) / 2;

	m_sprite.setPosition(x, y);
	m_sprite.setTexture(m_texture);
}

void LogoState::update(const float delta)
{
	UNUSED(delta);
}

void LogoState::mouseMoveEvent(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::mouseScrollEvent(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::keyPressedEvent(const sf::Event &event)
{
	UNUSED(event);

	m_stateHandler.changeState<TestState>(true);
}

void LogoState::keyReleasedEvent(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	target.draw(m_sprite);
}
