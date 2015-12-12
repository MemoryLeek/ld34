#include <fstream>
#include <iostream>
#include <regex>

#include <SFML/Graphics/RenderTarget.hpp>

#include <json.hpp>

#include "Map.h"
#include "Tileset.h"

using namespace Tiled;

Map::Map(const std::string& filename, const LightContext& lightContext)
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

			if (layer.find("type").value() == "objectgroup")
			{
				if (layerName == "lights")
				{
					const auto& lights = layer.find("objects").value();
					if (lights.is_null())
					{
						std::cout << "No lights" << std::endl;
					}
					else
					{
						std::cout << "Loading " << lights.size() << " light(s)." << std::endl;
						for (const auto& light : lights)
						{
							const auto& height = light.find("height").value().get<int>();
							const auto& width = light.find("width").value().get<int>();
							const auto& properties = light.find("properties").value();
							const auto& red = atoi(properties.find("r").value().get<std::string>().data());
							const auto& green = atoi(properties.find("g").value().get<std::string>().data());
							const auto& blue = atoi(properties.find("b").value().get<std::string>().data());
							const auto& x = light.find("x").value().get<int>() + width / 2;
							const auto& y = light.find("y").value().get<int>() + height / 2;

							const auto radius = (height > width) ? height : width;
							std::unique_ptr<Light> lp(new Light(lightContext, radius, sf::Color(red, green, blue)));
							lp->setPosition(x, y);
							m_lights.push_back(std::move(lp));
						}
					}
				}
				else if (layerName == "spawns")
				{
					const auto& spawns = layer.find("objects").value();
					if (spawns.is_null())
					{
						std::cout << "No spawns" << std::endl;
					}
					else
					{
						std::cout << "Loading " << spawns.size() << " spawn(s)." << std::endl;
						for (const auto& spawn : spawns)
						{
							const auto& x = spawn.find("x").value();
							const auto& y = spawn.find("y").value();
							m_spawnPoints.push_back(sf::Vector2i(x, y));
						}
					}
				}
				else if (layerName == "triggers")
				{
					const auto& triggers = layer.find("objects").value();
					if (triggers.is_null())
					{
						std::cout << "No triggers" << std::endl;
					}
					else
					{
						std::cout << "Loading " << triggers.size() << " trigger(s)." << std::endl;
						for (const auto& trigger : triggers)
						{
							const auto& x = trigger.find("x").value();
							const auto& y = trigger.find("y").value();
							const auto& width = trigger.find("width").value().get<int>();
							const auto& height = trigger.find("height").value().get<int>();
							const auto& name = trigger.find("name").value();
							const auto& type = trigger.find("type").value();
							m_triggerAreas.push_back(Trigger(name, type, x, y, width, height));
						}
					}
				}
			}
			else // tilelayer
			{
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

				const bool layerHasProperties = layer.find("properties") != layer.end();
				if (layerHasProperties)
				{
					const auto& layerProperties = layer.find("properties").value();
					for (auto it = layerProperties.begin(); it != layerProperties.end(); it++)
					{
						const bool propertyIsTrue = it.value() == "true";
						m_layers.back().setProperty(it.key(), propertyIsTrue);
					}
				}
			}
		}
	}
}

const std::vector<Layer>& Map::layers() const
{
	return m_layers;
}

const std::vector<std::unique_ptr<Light> > &Map::lights() const
{
	return m_lights;
}

const std::vector<sf::Vector2i> &Map::spawnPoints() const
{
	return m_spawnPoints;
}

const std::vector<Trigger> &Map::triggerAreas() const
{
	return m_triggerAreas;
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
