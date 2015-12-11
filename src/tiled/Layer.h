#ifndef LAYER_H
#define LAYER_H

#include <map>
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

			bool property(const std::string& name) const;
			Layer& setProperty(const std::string& name, bool isSet);

			bool hasTileAt(int x, int y) const;

		protected:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			const sf::Vector2u m_size;
			const std::vector<int> m_tileData;
			const std::vector<Tileset>& m_tilesets;
			std::vector<sf::VertexArray> m_vertexArrays;

			std::map<std::string, bool> m_properties;
	};
}

#endif // LAYER_H
