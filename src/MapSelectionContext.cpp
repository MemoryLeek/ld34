#include "MapSelectionContext.h"

MapSelectionContext::MapSelectionContext()
	: m_current(0)
{
	m_maps =
	{
		"maps/1.json",
		"maps/2.json",
		"maps/3.json",
		"maps/4.json",
		"maps/5.json",
	};
}

std::string MapSelectionContext::current() const
{
	return m_maps[m_current];
}

void MapSelectionContext::nextMap()
{
	if (m_current < 4)
	{
		m_current++;
	}
}
