#include "LightContext.h"

LightContext::LightContext(const Tiled::Map &map, const sf::Texture &screenSpaceNormalMap, const EntityManager &entityManager)
	: m_map(map)
	, m_screenSpaceNormalMap(screenSpaceNormalMap)
	, m_entityManager(entityManager)
{
}

const Tiled::Map &LightContext::map() const
{
	return m_map;
}

const sf::Texture &LightContext::screenSpaceNormalMap() const
{
	return m_screenSpaceNormalMap;
}

const EntityManager &LightContext::entityManager() const
{
	return m_entityManager;
}
