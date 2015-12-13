#include <iostream>

#include "Enemy.h"
#include "EntityManager.h"
#include "PlayerCharacter.h"
#include "Util.h"
#include "TurnHandler.h"

Enemy::Enemy(const sf::Texture &texture, const std::vector<PlayerCharacter *> &playerCharacters, const EntityCreationContext &context)
	: Character(texture, context)
	, m_playerCharacters(playerCharacters)
{

}

void Enemy::clone(const sf::Vector2f &destination)
{
	auto* newEnemy = new Enemy(m_texture, m_playerCharacters, m_creationContext);
	newEnemy->setPosition(destination);
	m_entityManager.add(newEnemy);
}

bool Enemy::turnStart(const float delta)
{
	UNUSED(delta);

	PlayerCharacter* closestPlayerAbove = nullptr;
	PlayerCharacter* closestPlayerBelow = nullptr;
	for (const auto& player : m_playerCharacters)
	{
		const bool isAbove = player->getPosition().y < getPosition().y;
		if (isAbove)
		{
			if (!closestPlayerAbove)
			{
				closestPlayerAbove = player;
			}
			else
			{
				const sf::Vector2f distanceToClosestAbove = closestPlayerAbove->getPosition() - getPosition();
				const sf::Vector2f distanceToThis = player->getPosition() - getPosition();
				if (abs(distanceToThis.y) < abs(distanceToClosestAbove.y))
				{
					closestPlayerAbove = player;
				}
			}
		}
		else
		{
			if (!closestPlayerBelow || closestPlayerBelow->getPosition().y < player->getPosition().y)
			{
				closestPlayerBelow = player;
			}
			else
			{
				const sf::Vector2f distanceToClosestAbove = closestPlayerBelow->getPosition() - getPosition();
				const sf::Vector2f distanceToThis = player->getPosition() - getPosition();
				if (abs(distanceToThis.y) < abs(distanceToClosestAbove.y))
				{
					closestPlayerBelow = player;
				}
			}
		}
	}

	PlayerCharacter* targetCharacter = (closestPlayerBelow) ? closestPlayerBelow : closestPlayerAbove;

	const bool isPlayerToTheRightOfMe = targetCharacter->getPosition().x > getPosition().x;
	int direction = (isPlayerToTheRightOfMe) ? 1 : -1;

	const bool isPlayerAboveMe = targetCharacter->getPosition().y < getPosition().y;
	const bool isNewPositionInTheAir = !getTileType(direction, 1);
	if (isNewPositionInTheAir && isPlayerAboveMe)
	{
		direction = getTileType(-direction, 1) ? -direction : direction ;
	}

	const bool isNewPositionAWall = getTileType(direction, 0);
	if (isNewPositionAWall)
	{
		direction = -direction;
	}

	setDirection(direction);

	const bool isPlayerRightNextToMe =
		abs(targetCharacter->getPosition().x - getPosition().x) == 32 &&
		targetCharacter->getPosition().y == getPosition().y;
	const bool isPlayerMovingAwayFromMe = targetCharacter->direction() == direction;
	if (isPlayerRightNextToMe && !isPlayerMovingAwayFromMe)
	{
		targetCharacter->setIsDead(true);
	}

	const bool willPlayerEndUpInTheSameTileAsI =
		abs(targetCharacter->getPosition().x + (targetCharacter->direction() * 32) - getPosition().x) == 32 &&
		targetCharacter->getPosition().y == getPosition().y;
	if (willPlayerEndUpInTheSameTileAsI)
	{
		targetCharacter->setIsDead(true);
	}

	return true;
}

void Enemy::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
}

bool Enemy::handlePowerUp(int type, float delta)
{
	UNUSED(type);

	return true;
}
