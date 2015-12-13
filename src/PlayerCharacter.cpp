#include "EntityManager.h"
#include "PlayerCharacter.h"
#include "Util.h"

PlayerCharacter::PlayerCharacter(const sf::Texture &texture, std::vector<PlayerCharacter*> &playerCharacterList, const EntityCreationContext &context)
	: Character(texture, context)
	, m_playerCharacterList(playerCharacterList)
	, m_powerUp(Neutral)
	, m_powerUpTimer(0)
{

}

bool PlayerCharacter::turnStart(const float delta)
{
	UNUSED(delta);

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
	auto* newCharacter = new PlayerCharacter(m_texture, m_playerCharacterList, m_creationContext);
	newCharacter->setPosition(destination);

	m_playerCharacterList.push_back(newCharacter);
}
