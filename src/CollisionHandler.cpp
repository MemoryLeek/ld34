#include <iostream>

#include "CollisionHandler.h"
#include "Util.h"
#include "tiled/Map.h"
#include "tiled/Trigger.h"

CollisionHandler::CollisionHandler(const Tiled::Map &map)
	: m_map(map)
{
}

int CollisionHandler::getTileType(int x, int y) const
{
	for (const auto& layer : m_map.layers())
	{
		if (layer.property("collidable"))
		{
			return layer.tileAt(x, y);
		}
	}

	return 0;
}

std::vector<Tiled::Trigger> CollisionHandler::getTriggers(int x, int y) const
{
	std::vector<Tiled::Trigger> triggers;

	for (const auto& trigger : m_map.triggerAreas())
	{
		if (trigger.contains(x, y))
		{
			triggers.push_back(trigger);
		}
	}

	return triggers;
}

std::vector<Tiled::Trigger> CollisionHandler::getTriggers(const sf::Vector2f& pos) const
{
	return getTriggers(pos.x, pos.y);
}
