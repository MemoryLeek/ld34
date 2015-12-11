#ifndef ISTATE
#define ISTATE

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

class IState : public sf::Drawable
{
	public:
		virtual ~IState() = default;

		virtual void update(const float delta) = 0;

		virtual void mouseMoveEvent(const sf::Event &event) = 0;
		virtual void mouseScrollEvent(const sf::Event &event) = 0;

		virtual void keyPressedEvent(const sf::Event &event) = 0;
		virtual void keyReleasedEvent(const sf::Event &event) = 0;
};

#endif // ISTATE

