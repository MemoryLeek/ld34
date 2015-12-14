#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>

#include "Layer.h"
#include "Light.h"
#include "Tileset.h"
#include "Trigger.h"

namespace Tiled
{
	class Map : public sf::Drawable
	{
		public:
			Map(const std::string& filename, const LightContext& lightContext);

			const sf::Vector2i size() const;
			const std::vector<Layer>& layers() const;
			const std::vector<std::unique_ptr<Light>>& lights() const;
			const std::vector<sf::Vector2i>& spawnPoints() const;
			const std::vector<sf::Vector2i>& playerSpawnPoints() const;
			const std::vector<Trigger>& triggerAreas() const;


			void drawBackgroundNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;

		protected:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			sf::Vector2i m_size;
			std::vector<Tileset> m_tilesets;
			std::vector<Layer> m_layers;
			std::vector<std::unique_ptr<Light>> m_lights;
			std::vector<sf::Vector2i> m_spawnPoints;
			std::vector<sf::Vector2i> m_playerSpawnPoints;
			std::vector<Trigger> m_triggerAreas;
	};
}

#endif // MAP_H
