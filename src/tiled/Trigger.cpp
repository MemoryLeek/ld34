#include "Trigger.h"

using namespace Tiled;

Trigger::Trigger(const std::string &name, const std::string &type, int x, int y, int width, int height)
	: sf::IntRect(x, y, width, height)
	, m_type(type)
{
}

std::string Trigger::type() const
{
	return m_type;
}

std::string Trigger::property(const std::string &name) const
{
	const auto& property = m_properties.find(name);
	if (property != m_properties.end())
	{
		return property->second;
	}

	return "";
}

void Trigger::setProperty(const std::string &name, const std::string &value)
{
	m_properties[name] = value;
}

