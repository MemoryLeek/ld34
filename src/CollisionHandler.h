#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

namespace Tiled
{
	class Map;
}

class CollisionHandler
{
	public:
		CollisionHandler(const Tiled::Map& map);

		bool isCollidable(int x, int y) const;

	private:
		const Tiled::Map& m_map;
};

#endif // COLLISIONHANDLER_H
