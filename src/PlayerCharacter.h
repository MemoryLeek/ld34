#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Entity.h"

class PlayerCharacter : public Entity
{
	public:
		PlayerCharacter(const sf::Texture &texture, std::vector<PlayerCharacter *> &playerCharacterList, const EntityCreationContext &context);

	protected:
		bool turnStart(const float delta) override;
		void handleMove(const float delta, const int direction) override;
		void clone(const sf::Vector2f &destination) override;

	private:
		std::vector<PlayerCharacter*> &m_playerCharacterList;
};

#endif // PLAYERCHARACTER_H
