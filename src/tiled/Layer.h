#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include "Tileset.h"

namespace Tiled
{
	class Layer : public sf::Drawable
	{
		public:
			Layer(const sf::Vector2u& size, const std::vector<int>& tileData, const std::vector<Tileset>& tilesets);

			void drawNormalsTo(sf::RenderTarget &target, sf::RenderStates states) const;

		protected:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			const std::vector<Tileset>& m_tilesets;
			std::vector<sf::VertexArray> m_vertexArrays;
	};
}

#endif // LAYER_H
