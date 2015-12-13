#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <SFML/Graphics/Drawable.hpp>

class StateCreationContext;
class IState;

class StateHandler : public sf::Drawable
{
	const float TRANSITION_LENGTH = 1000;

	public:
		StateHandler(sf::RenderWindow &window);

		IState &currentState() const;

		template<class TState>
		void changeState(bool transition)
		{
			if (m_progress <= 0)
			{
				StateCreationContext context(*this, m_window);

				if (transition)
				{
					m_nextState = new TState(context);
					m_progress = TRANSITION_LENGTH;
				}
				else
				{
					delete m_currentState;

					m_currentState = new TState(context);
				}
			}
		}

		void update(double delta);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::RenderWindow &m_window;

		IState *m_currentState;
		IState *m_nextState;

		float m_progress;
};

#endif // STATEHANDLER_H
