#include <fstream>
#include <iostream>
#include <regex>

#include <SFML/Graphics/RenderTarget.hpp>

#include <json.hpp>

#include "Map.h"
#include "Tileset.h"

using namespace Tiled;

Map::Map(const std::string &filename)
{
	// Don't use the stream API in SFML, it sucks
	std::ifstream stream(filename);;
	auto json = nlohmann::json::parse(stream);

	//const auto mapSize = sf::Vector2i(json.find("width").value(), json.find("height").value());

//	std::cout << json << std::endl;

	const auto& tilesets = json.find("tilesets").value();
	if (tilesets.is_null() || tilesets.size() == 0)
	{
		std::cout << "No tilesets" << std::endl;
	}
	else
	{
		std::cout << "Loading " << tilesets.size() << " tileset(s)." << std::endl;
		for (auto& tileset : tilesets)
		{
			const auto& firstGid = tileset.find("firstgid").value();
			const auto& tileCount = tileset.find("tilecount").value();
			const auto& tileSize = sf::Vector2u(tileset.find("tilewidth").value(), tileset.find("tileheight").value());
			// Tileset path is relative from the maps/ folder, i.e. remove ../
			const auto& texturePath = std::regex_replace(
				tileset.find("image").value().get<std::string>(),
				std::regex("^\\.\\./"),
				""
			);

			m_tilesets.push_back(Tileset(firstGid, tileCount, tileSize, texturePath));
		}
	}

	const auto& layers = json.find("layers").value();
	if (layers.is_null() || layers.size() == 0)
	{
		std::cout << "No layers" << std::endl;
	}
	else
	{
		std::cout << "Loading " << layers.size() << " layer(s)." << std::endl;
		for (const auto &layer : layers)
		{
			const auto& layerName = layer.find("name").value();
			const auto& layerSize = sf::Vector2u(layer.find("width").value(), layer.find("height").value());
			std::cout << "Loading " << layerName << std::endl;

			const bool isLayerDataEncoded = layer.find("encoding") != layer.end();
			if (isLayerDataEncoded)
			{
				std::cout
					<< "Layer "
					<< layerName
					<< " is encoded, this is not supported, use CSV." << std::endl;
				continue;
			}

			std::vector<int> tileArray;
			for (const auto &id : layer.find("data").value())
			{
				tileArray.push_back(id);
			}

			if (tileArray.size() != static_cast<size_t>(layerSize.x * layerSize.y))
			{
				std::cout << "Layer data did not match layer size" << std::endl;
				continue;
			}

			m_layers.push_back(Layer(layerSize, tileArray, m_tilesets));
		}
	}
}

void Map::drawBackgroundNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const auto& layer : m_layers)
	{
		layer.drawNormalsTo(target, states);
	}
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const auto& layer : m_layers)
	{
		target.draw(layer, states);
	}
}
