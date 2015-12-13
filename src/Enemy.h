#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include "Character.h"

class PlayerCharacter;

class Enemy : public Character
{
	public:
		Enemy(const sf::Texture &texture, const std::vector<PlayerCharacter*> &playerCharacters, const EntityCreationContext &context);

	protected:
		void clone(const sf::Vector2f &destination) override;

	private:
		bool turnStart(const float delta) override;
		void handleMove(const float delta, const int direction) override;

		const std::vector<PlayerCharacter*> &m_playerCharacters;
};

#endif // ENEMY_H
