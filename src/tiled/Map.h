#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>

#include "Layer.h"
#include "Light.h"
#include "Tileset.h"

namespace Tiled
{
	class Map : public sf::Drawable
	{
		public:
			Map(const std::string& filename, const LightContext& lightContext);

			const std::vector<Layer>& layers() const;
			const std::vector<std::unique_ptr<Light>>& lights() const;
			const std::vector<sf::Vector2i>& spawnPoints() const;


			void drawBackgroundNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;

		protected:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			std::vector<Tileset> m_tilesets;
			std::vector<Layer> m_layers;
			std::vector<std::unique_ptr<Light>> m_lights;
			std::vector<sf::Vector2i> m_spawnPoints;
	};
}

#endif // MAP_H
