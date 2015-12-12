#ifndef LIGHTCONTEXT_H
#define LIGHTCONTEXT_H

#include <SFML/Graphics/Texture.hpp>

namespace Tiled
{
	class Map;
}

class Entity;

class LightContext
{
	public:
		LightContext(const Tiled::Map& map, const sf::Texture& screenSpaceNormalMap, const std::vector<Entity*>& shadowCastingEntities);

		const Tiled::Map& map() const;
		const sf::Texture& screenSpaceNormalMap() const;
		const std::vector<Entity*>& shadowCastingEntities() const;

	private:
		const Tiled::Map& m_map;
		const sf::Texture& m_screenSpaceNormalMap;
		const std::vector<Entity*>& m_shadowCastingEntities;
};

#endif // LIGHTCONTEXT_H
