#include "Enemy.h"

Enemy::Enemy(const sf::Texture& diffuseTexture, const sf::Texture& normalTexture, CollisionHandler &collisionHandler, EntityManager &entityManager)
	: Entity(diffuseTexture, normalTexture, collisionHandler, entityManager)
{

}

