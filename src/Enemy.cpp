#include <iostream>

#include "Enemy.h"
#include "PlayerCharacter.h"
#include "Util.h"
#include "TurnHandler.h"

Enemy::Enemy(const sf::Texture &texture, PlayerCharacter &player, const EntityCreationContext &context)
	: Entity(texture, context)
	, m_player(player)
{

}

void Enemy::turnStart(const float delta)
{
	UNUSED(delta);

	const bool isPlayerRightNextToMe =
		abs(m_player.getPosition().x - getPosition().x) == 32 &&
		m_player.getPosition().y == getPosition().y;
	if (isPlayerRightNextToMe)
	{
		*reinterpret_cast<int*>(0xDEADBEEF) = 0xF00BAA;
	}

	const bool isPlayerToTheRightOfMe = m_player.getPosition().x > getPosition().x;
	int direction = (isPlayerToTheRightOfMe) ? 1 : -1;

	const bool isPlayerAboveMe = m_player.getPosition().y < getPosition().y;
	const bool isNewPositionInTheAir = !isCollidable(direction, 1);
	if (isNewPositionInTheAir && isPlayerAboveMe)
	{
		direction = -direction;
	}

	setDirection(direction);
}

void Enemy::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
}
