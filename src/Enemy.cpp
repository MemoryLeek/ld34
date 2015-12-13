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

bool Enemy::turnStart(const float delta)
{
	UNUSED(delta);

	const bool isPlayerToTheRightOfMe = m_player.getPosition().x > getPosition().x;
	int direction = (isPlayerToTheRightOfMe) ? 1 : -1;

	const bool isPlayerAboveMe = m_player.getPosition().y < getPosition().y;
	const bool isNewPositionInTheAir = !isCollidable(direction, 1);
	if (isNewPositionInTheAir && isPlayerAboveMe)
	{
		direction = isCollidable(-direction, 1) ? -direction : direction ;
	}

	const bool isNewPositionAWall = isCollidable(direction, 0);
	if (isNewPositionAWall)
	{
		direction = -direction;
	}

	setDirection(direction);

	const bool isPlayerRightNextToMe =
		abs(m_player.getPosition().x - getPosition().x) == 32 &&
		m_player.getPosition().y == getPosition().y;
	const bool isPlayerMovingAwayFromMe = m_player.direction() == direction;
	if (isPlayerRightNextToMe && !isPlayerMovingAwayFromMe)
	{
		m_player.kill();
	}

	const bool willPlayerEndUpInTheSameTileAsI =
		abs(m_player.getPosition().x + (m_player.direction() * 32) - getPosition().x) == 32 &&
		m_player.getPosition().y == getPosition().y;
	if (willPlayerEndUpInTheSameTileAsI)
	{
		m_player.kill();
	}

	return true;
}

void Enemy::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
}
