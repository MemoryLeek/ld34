#include "LightContext.h"

LightContext::LightContext(const Tiled::Map &map, const sf::Texture &screenSpaceNormalMap, const std::vector<Entity *> &shadowCastingEntities)
	: m_map(map)
	, m_screenSpaceNormalMap(screenSpaceNormalMap)
	, m_shadowCastingEntities(shadowCastingEntities)
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

const std::vector<Entity *> &LightContext::shadowCastingEntities() const
{
	return m_shadowCastingEntities;
}
