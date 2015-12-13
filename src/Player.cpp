#include "Player.h"
#include "PlayerCharacter.h"
#include "Util.h"

Player::Player(const sf::Texture &texture, const EntityCreationContext &context)
	: m_texture(texture)
	, m_context(context)
{
//	PlayerCharacter *character = new PlayerCharacter(m_texture, m_characters, m_context);
//	character->setPosition(destination);
}

void Player::setDirection(int direction)
{
	for (PlayerCharacter *character : m_characters)
	{
		character->setDirection(direction);
	}
}
