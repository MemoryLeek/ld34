#include "StatusIndicators.h"

StatusIndicators::StatusIndicators(const sf::Texture &tnt, const sf::Texture &snowflake)
	: m_tnt(tnt)
	, m_snowflake(snowflake)
{
}

const sf::Texture &StatusIndicators::tnt() const
{
	return m_tnt;
}

const sf::Texture &StatusIndicators::snowflake() const
{
	return m_snowflake;
}
