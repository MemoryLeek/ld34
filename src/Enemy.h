#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
	public:
		Enemy(const sf::Texture &diffuseTexture, const sf::Texture &normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager);
};

#endif // ENEMY_H
