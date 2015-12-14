#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "tiled/Trigger.h"

namespace Tiled
{
	class Map;
}

class CollisionHandler
{
	public:
		CollisionHandler(const Tiled::Map& map);

		int getTileType(int x, int y) const;
		bool isOnMapBottom(int y) const;

		std::vector<Tiled::Trigger> getTriggers(int x, int y) const;
		std::vector<Tiled::Trigger> getTriggers(const sf::Vector2f& pos) const;

	private:
		const Tiled::Map& m_map;
};

#endif // COLLISIONHANDLER_H
