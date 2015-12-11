#include <iostream>
#include <regex>

#include "Tileset.h"

Tileset::Tileset()
{
}

Tileset::Tileset(int firstGid, int tileCount, const sf::Vector2u &tileSize, const std::string &filepath)
	: m_firstGid(firstGid)
	, m_tileCount(tileCount)
	, m_tileSize(tileSize)
{
	if (!m_diffuseTexture.loadFromFile(filepath))
	{
		std::cout << "Failed to load tileset diffuse texture: " << filepath << std::endl;
	}

	// Load corresponding normal map
	const auto& normalMapPath = std::regex_replace(
		filepath,
		std::regex("\\.png$"),
		"_n.png"
	);
	if (!m_normalTexture.loadFromFile(normalMapPath))
	{
		std::cout << "Failed to load tileset normal texture: " << normalMapPath << std::endl;
	}
}

int Tileset::firstGid() const
{
	return m_firstGid;
}

int Tileset::count() const
{
	return m_tileCount;
}

sf::Vector2u Tileset::tileSize() const
{
	return m_tileSize;
}

sf::Vector2u Tileset::textureSize() const
{
	return m_diffuseTexture.getSize();
}

const sf::Texture* Tileset::diffuseTexture() const
{
	return &m_diffuseTexture;
}

const sf::Texture* Tileset::normalTexture() const
{
	return &m_normalTexture;
}
