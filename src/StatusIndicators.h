#ifndef STATUSINDICATORS_H
#define STATUSINDICATORS_H

#include <SFML/Graphics/Texture.hpp>

class StatusIndicators
{
	public:
		StatusIndicators(const sf::Texture& tnt, const sf::Texture& snowflake);

		const sf::Texture& tnt() const;
		const sf::Texture& snowflake() const;

	private:
		const sf::Texture& m_tnt;
		const sf::Texture& m_snowflake;
};

#endif // STATUSINDICATORS_H
