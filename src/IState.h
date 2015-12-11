#ifndef ISTATE
#define ISTATE

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

class IState : public sf::Drawable
{
	public:
		virtual void update(const sf::Time& delta) = 0;

		virtual void mouseMoveEvent(const sf::Event &event) = 0;
		virtual void mouseScrollEvent(const sf::Event &event) = 0;

		virtual void keyDownEvent(const sf::Event &event) = 0;
		virtual void keyUpEvent(const sf::Event &event) = 0;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif // ISTATE

