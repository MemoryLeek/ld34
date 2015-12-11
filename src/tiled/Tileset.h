#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Tileset
{
	public:
		Tileset();
		Tileset(int firstGid, int tileCount, const sf::Vector2u& tileSize, const std::string& filepath);

		int firstGid() const;
		int count() const;

		sf::Vector2u tileSize() const;
		sf::Vector2u textureSize() const;

		const sf::Texture* diffuseTexture() const;
		const sf::Texture* normalTexture() const;

	private:
		int m_firstGid;
		int m_tileCount;
		sf::Vector2u m_tileSize;
		sf::Texture m_diffuseTexture;
		sf::Texture m_normalTexture;
};

#endif // TILESET_H
