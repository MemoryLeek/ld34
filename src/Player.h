#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "IEntity.h"

class PlayerCharacter;
class EntityCreationContext;

class Player
{
	public:
		Player(const sf::Texture &texture, const EntityCreationContext &context);

		void setDirection(int direction);

	private:
		const sf::Texture &m_texture;
		const EntityCreationContext &m_context;

		std::vector<PlayerCharacter *> m_characters;
};

#endif // PLAYER_H
