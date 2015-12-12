#ifndef LIGHTCONTEXT_H
#define LIGHTCONTEXT_H

#include <SFML/Graphics/Texture.hpp>

namespace Tiled
{
	class Map;
}

class Entity;
class EntityManager;

class LightContext
{
	public:
		LightContext(const Tiled::Map& map, const sf::Texture& screenSpaceNormalMap, const EntityManager &entityManager);

		const Tiled::Map& map() const;
		const sf::Texture& screenSpaceNormalMap() const;
		const EntityManager &entityManager() const;

	private:
		const Tiled::Map& m_map;
		const sf::Texture& m_screenSpaceNormalMap;
		const EntityManager &m_entityManager;
};

#endif // LIGHTCONTEXT_H
