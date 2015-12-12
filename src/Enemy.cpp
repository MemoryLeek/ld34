#include <iostream>

#include "Enemy.h"
#include "Util.h"

Enemy::Enemy(ITextureProvider &textureProvider, PlayerCharacter &player, const EntityCreationContext &context)
	: Entity(textureProvider, context)
	, m_player(player)
{

}

void Enemy::turnStart(const float delta)
{
	UNUSED(delta);

	setDirection(1);
}

void Enemy::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
}
