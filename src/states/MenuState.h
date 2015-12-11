#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "IState.h"

class MenuDefinitionBuilder;
class StateCreationContext;
class StateHandler;

class MenuState : public IState
{
	public:
		MenuState(StateCreationContext &context);

		void update(const float delta) override;

		void mouseMoveEvent(const sf::Event &event) override;
		void mouseScrollEvent(const sf::Event &event) override;

		void keyPressedEvent(const sf::Event &event) override;
		void keyReleasedEvent(const sf::Event &event) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		virtual void definition(MenuDefinitionBuilder &builder) = 0;

	private:
		StateHandler &m_stateHandler;
};

#endif // MENUSTATE_H
