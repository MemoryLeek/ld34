#ifndef MAP_H
#define MAP_H

#include <string>

#include <SFML/Graphics/Drawable.hpp>

#include "Layer.h"
#include "Tileset.h"

namespace Tiled
{
	class Map : public sf::Drawable
	{
		public:
			Map(const std::string& filename);

			void drawBackgroundNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;

		protected:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			std::vector<Tileset> m_tilesets;
			std::vector<Layer> m_layers;
	};
}

#endif // MAP_H
