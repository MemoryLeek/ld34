#include "ITextureProvider.h"

TextureProvider::TextureProvider(const std::string &diffuseFileName, const std::string &normalFileName)
{
	m_diffuseTexture.loadFromFile(diffuseFileName);
	m_normalTexture.loadFromFile(normalFileName);
}

const sf::Texture &TextureProvider::diffuseTexture() const
{
	return m_diffuseTexture;
}

const sf::Texture &TextureProvider::normalTexture() const
{
	return m_normalTexture;
}

PlayerCharacterTextureProvider::PlayerCharacterTextureProvider()
	: TextureProvider("sprites/cube.png", "sprites/cube_n.png")
{

}

EnemyTextureProvider::EnemyTextureProvider()
	: TextureProvider("sprites/cube.png", "sprites/cube_n.png")
{

}
