#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
	public:
		Enemy(ITextureProvider &textureProvider, const EntityCreationContext &context);
};

#endif // ENEMY_H
