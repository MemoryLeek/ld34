#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"

class StatusIndicators;

class PlayerCharacter : public Character
{
	public:
		PlayerCharacter(const sf::Texture &texture, const StatusIndicators &statusIndicators, std::vector<PlayerCharacter *> &playerCharacterList, const EntityCreationContext &context);

		bool isHuge() const;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		bool turnStart(const float delta) override;

		void handleMove(const float delta, const int direction) override;
		bool handlePowerUp(int type, float delta) override;

		void clone(const sf::Vector2f &destination) override;

	private:
		const StatusIndicators &m_statusIndicators;
		std::vector<PlayerCharacter*> &m_playerCharacterList;

		int m_powerUp;

		float m_powerUpTimer;
		int m_kaboomTickTimer;
		int m_frozenTickTimer;
};

#endif // PLAYERCHARACTER_H
