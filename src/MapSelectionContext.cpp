#include "MapSelectionContext.h"

MapSelectionContext::MapSelectionContext()
	: m_current(0)
{
	m_maps =
	{
		"maps/5.json",
		"maps/2.json",
		"maps/3.json",
		"maps/4.json"
	};
}

std::string MapSelectionContext::current() const
{
	return m_maps[m_current];
}

void MapSelectionContext::nextMap()
{
	if (m_current < 3)
	{
		m_current++;
	}
}
