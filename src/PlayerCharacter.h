#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"

class PlayerCharacter : public Character
{
	public:
		PlayerCharacter(const sf::Texture &texture, std::vector<PlayerCharacter *> &playerCharacterList, const EntityCreationContext &context);

	protected:
		bool turnStart(const float delta) override;

		void handleMove(const float delta, const int direction) override;
		bool handlePowerUp(int type, float delta) override;

		void clone(const sf::Vector2f &destination) override;

	private:
		std::vector<PlayerCharacter*> &m_playerCharacterList;

		int m_powerUp;

		float m_powerUpTimer;
		int m_frozenTickTimer;
};

#endif // PLAYERCHARACTER_H
