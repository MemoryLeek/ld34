#include "PlayerCharacter.h"
#include "Util.h"

PlayerCharacter::PlayerCharacter(const sf::Texture &texture, const EntityCreationContext &context)
	: Entity(texture, context)
{

}

void PlayerCharacter::turnStart(const float delta)
{
	UNUSED(delta);
}

void PlayerCharacter::handleMove(const float delta, const int direction)
{
	move(direction * (delta * 128), 0);
	rotate(direction * (delta * 360));
}
