#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
	public:
		Enemy(const EntityCreationContext &context);
};

#endif // ENEMY_H