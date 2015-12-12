#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"

class PlayerCharacter : public Entity
{
	public:
		PlayerCharacter(const EntityCreationContext &context);
};

#endif // PLAYERCHARACTER_H
