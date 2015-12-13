#ifndef IENTITY
#define IENTITY

#include <unordered_set>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "ITurn.h"

class IEntity
	: public sf::Drawable
	, public sf::Transformable
	, public ITurn
{
	public:
		virtual int direction() const = 0;
		virtual void setDirection(int direction) = 0;

		virtual bool isDead() const = 0;
		virtual void setIsDead(bool isDead) = 0;

	protected:
		virtual void handleMove(const float delta, const int direction) = 0;
		virtual void clone(const sf::Vector2f &destination) = 0;
};

#endif // IENTITY

