#include <SFML/Graphics/RenderTarget.hpp>

#include "EntityManager.h"
#include "PlayerCharacter.h"
#include "StatusIndicators.h"
#include "Util.h"

PlayerCharacter::PlayerCharacter(const sf::Texture &texture, const StatusIndicators &statusIndicators, std::vector<PlayerCharacter*> &playerCharacterList, const EntityCreationContext &context)
	: Character(texture, context)
	, m_statusIndicators(statusIndicators)
	, m_playerCharacterList(playerCharacterList)
	, m_powerUp(Neutral)
	, m_powerUpTimer(0)
	, m_kaboomTickTimer(0)
	, m_frozenTickTimer(0)
{

}

void PlayerCharacter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Character::draw(target, states);

	if (m_kaboomTickTimer)
	{
		sf::Sprite bomb(m_statusIndicators.tnt());
		bomb.setPosition(getPosition() + sf::Vector2f(0, -64));
		target.draw(bomb);
	}

	if (m_frozenTickTimer)
	{
		sf::Sprite snowflake(m_statusIndicators.snowflake());
		snowflake.setPosition(getPosition() + sf::Vector2f(0, -64));
		target.draw(snowflake);
	}
}

bool PlayerCharacter::turnStart(const float delta)
{
	UNUSED(delta);

	if (m_kaboomTickTimer > 0)
	{
		m_kaboomTickTimer--;
		if (!m_kaboomTickTimer)
		{
			// Kill everything within a certain radius
			for (const auto& entity : m_entityManager.entities())
			{
				const auto distanceVector = entity->getPosition() - getPosition();
				const auto killRadius = 32 * 5;
				if (sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y) < killRadius)
				{
					entity->setIsDead(true);
				}
			}
		}
	}

	if (m_frozenTickTimer > 0)
	{
		m_frozenTickTimer--;
	}

	return true;
}

void PlayerCharacter::handleMove(const float delta, const int direction)
{
	if (m_frozenTickTimer > 0)
	{
		return;
	}

	move(direction * (delta * 128), 0);
	rotate(direction * (delta * 360));
}

bool PlayerCharacter::handlePowerUp(int type, float delta)
{
	if (m_powerUp == type)
	{
		return true;
	}

	if ((m_powerUpTimer += delta) > 0.25f)
	{
		m_powerUp = type;
		m_powerUpTimer = 0;

		return true;
	}

	switch (type)
	{
		case Growing:
		{
			setScale(2, 2);
//			scale(delta * 2, delta * 2);

			break;
		}
		case Explosive:
		{
			m_kaboomTickTimer = 5;
			break;
		}
		case Frozen:
		{
			m_frozenTickTimer = 5;
			break;
		}
	}

	return false;
}

void PlayerCharacter::clone(const sf::Vector2f &destination)
{
	auto* newCharacter = new PlayerCharacter(m_texture, m_statusIndicators, m_playerCharacterList, m_creationContext);
	newCharacter->setPosition(destination);

	m_playerCharacterList.push_back(newCharacter);
}
