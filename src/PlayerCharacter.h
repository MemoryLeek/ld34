#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"

class PlayerCharacter : public Entity
{
	public:
		PlayerCharacter(const sf::Texture &texture, const EntityCreationContext &context);

	protected:
		void turnStart(const float delta) override;
		void handleMove(const float delta, const int direction) override;
};

#endif // PLAYERCHARACTER_H
