#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IState.h"

class StateHandler;
class StateCreationContext;

class LogoState : public IState
{
	public:
		LogoState(StateCreationContext &context);

		void update(const float delta) override;

		void mouseMoveEvent(const sf::Event &event) override;
		void mouseScrollEvent(const sf::Event &event) override;

		void keyPressedEvent(const sf::Event &event) override;
		void keyReleasedEvent(const sf::Event &event) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		StateHandler &m_stateHandler;

		sf::RenderWindow &m_window;
		sf::Texture m_texture;
		sf::Sprite m_sprite;
};

#endif // LOGOSTATE_H
