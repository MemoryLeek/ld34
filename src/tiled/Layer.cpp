#include <iostream>
#include <set>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Layer.h"

using namespace Tiled;

Layer::Layer(const sf::Vector2u &size, const std::vector<int> &tileData, const std::vector<Tileset> &tilesets)
	: m_size(size)
	, m_tileData(tileData)
	, m_tilesets(tilesets)
{
	// When drawing a layer we want to to as few texture switches as possible
	// to get highest performance, to do this we keep separate vertex arrays for
	// the separate tilesets, I probably shouldn't depend on the ordering/size
	// of the tilesets vector but I'm tired so meh
	m_vertexArrays.resize(tilesets.size());

	int i = 0;
	for (const auto& tileset : tilesets)
	{
		m_vertexArrays[i].setPrimitiveType(sf::Quads);

		const auto& lowestTileId = tileset.firstGid();
		const auto& highestTileId = lowestTileId + tileset.count();
		const auto& textureWidth = tileset.textureSize().x;
		const auto& tileSize = tileset.tileSize();

		for (uint x = 0; x < size.x; x++)
		{
			for(uint y = 0; y < size.y; y++)
			{
				const auto& tileType = tileData[x + y * size.x];
				const bool isTileTypeInCurrentTileset =
					tileType >= lowestTileId &&
					tileType <= highestTileId;
				if(!isTileTypeInCurrentTileset)
				{
					continue;
				}

				// Texture coords
				uint tx = (tileType - lowestTileId) % (textureWidth / tileSize.x);
				uint ty = (tileType - lowestTileId) / (textureWidth / tileSize.x);

				auto& va = m_vertexArrays[i];
				sf::Vertex vertex;
				// Top left
				vertex.position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
				vertex.texCoords = sf::Vector2f(tx * tileSize.x, ty * tileSize.y);
				va.append(vertex);
				// Top right
				vertex.position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
				vertex.texCoords = sf::Vector2f((tx + 1) * tileSize.x, ty * tileSize.y);
				va.append(vertex);
				// Bottom right
				vertex.position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
				vertex.texCoords = sf::Vector2f((tx + 1) * tileSize.x, (ty + 1) * tileSize.y);
				va.append(vertex);
				// Bottom left
				vertex.position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
				vertex.texCoords = sf::Vector2f(tx * tileSize.x, (ty + 1) * tileSize.y);
				va.append(vertex);
			}
		}

		i++;
	}
}

void Layer::drawNormalsTo(sf::RenderTarget &target, sf::RenderStates states) const
{
	int i = 0;
	for (const auto& tileset : m_tilesets)
	{
		states.texture = tileset.normalTexture();

		target.draw(m_vertexArrays[i], states);

		i++;
	}
}

bool Layer::property(const std::string &name) const
{
	const auto& property = m_properties.find(name);
	if (property != m_properties.end())
	{
		return property->second;
	}

	return false;
}

Layer& Layer::setProperty(const std::string &name, bool isSet)
{
	m_properties[name] = isSet;
	return *this;
}

bool Layer::hasTileAt(int x, int y) const
{
	return m_tileData[x + 1 + y * m_size.x] > 0;
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	int i = 0;
	for (const auto& tileset : m_tilesets)
	{
		states.texture = tileset.diffuseTexture();

		target.draw(m_vertexArrays[i], states);

		i++;
	}
}
