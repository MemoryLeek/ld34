#include <iostream>

#include "CollisionHandler.h"
#include "Util.h"
#include "tiled/Map.h"

CollisionHandler::CollisionHandler(const Tiled::Map &map)
	: m_map(map)
{
}

bool CollisionHandler::isCollidable(int x, int y) const
{
	for (const auto& layer : m_map.layers())
	{
		if (layer.property("collidable") && layer.hasTileAt(x, y))
		{
			return true;
		}
	}

	return false;
}

