#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"

class MainMenuState : public MenuState
{
	public:
		MainMenuState(StateCreationContext &context);

	protected:
		void definition(MenuDefinitionBuilder &builder) override;
};

#endif // MAINMENUSTATE_H
