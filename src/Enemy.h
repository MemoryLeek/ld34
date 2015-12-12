#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class PlayerCharacter;

class Enemy : public Entity
{
	public:
		Enemy(const sf::Texture &texture, PlayerCharacter &player, const EntityCreationContext &context);

	private:
		bool turnStart(const float delta) override;
		void handleMove(const float delta, const int direction) override;

		PlayerCharacter &m_player;
};

#endif // ENEMY_H
