#include "EntityManager.h"
#include "PlayerCharacter.h"
#include "Util.h"

PlayerCharacter::PlayerCharacter(const sf::Texture &texture, std::vector<PlayerCharacter*> &playerCharacterList, const EntityCreationContext &context)
	: Character(texture, context)
	, m_playerCharacterList(playerCharacterList)
{

}

bool PlayerCharacter::turnStart(const float delta)
{
	UNUSED(delta);

	return true;
}

void PlayerCharacter::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
	rotate(direction * (delta * 360));
}

void PlayerCharacter::clone(const sf::Vector2f &destination)
{
	auto* newCharacter = new PlayerCharacter(m_texture, m_playerCharacterList, m_creationContext);
	newCharacter->setPosition(destination);

	m_playerCharacterList.push_back(newCharacter);
}
