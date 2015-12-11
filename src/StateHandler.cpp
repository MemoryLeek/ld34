#include <math.h>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "states/LogoState.h"

#include "StateCreationContext.h"
#include "StateHandler.h"
#include "IState.h"

StateHandler::StateHandler(sf::RenderWindow &window)
	: m_window(window)
	, m_currentState(nullptr)
	, m_nextState(nullptr)
	, m_progress(0)
{
	changeState<LogoState>(false);
}

IState &StateHandler::currentState() const
{
	return *m_currentState;
}

void StateHandler::update(double delta)
{
	if (m_progress > 0)
	{
		if ((m_progress -= delta * 1000) <= (TRANSITION_LENGTH / 2.0f))
		{
			if (m_nextState)
			{
				delete m_currentState;

				m_currentState = m_nextState;
				m_nextState = nullptr;
			}
		}
	}

	if (m_currentState)
	{
		m_currentState->update(delta);
	}
}

void StateHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_currentState)
	{
		target.draw(*m_currentState, states);
	}

	if (m_progress > 0)
	{
		const float progress = std::min(TRANSITION_LENGTH, m_progress) / TRANSITION_LENGTH;
		const float alpha = sin(progress * M_PI) * 255.0f;

		if (alpha >= 0)
		{
			const sf::Vector2f size = (sf::Vector2f)m_window.getSize();
			const sf::Color color(0, 0, 0, alpha);

			sf::RectangleShape rectangle(size);
			rectangle.setFillColor(color);

			target.draw(rectangle);
		}
	}
}
