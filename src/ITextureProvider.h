#ifndef ITEXTUREPROVIDER
#define ITEXTUREPROVIDER

#include <SFML/Graphics/Texture.hpp>

class ITextureProvider
{
	public:
		virtual const sf::Texture &diffuseTexture() const = 0;
		virtual const sf::Texture &normalTexture() const = 0;
};

class TextureProvider : public ITextureProvider
{
	public:
		TextureProvider(const std::string &diffuseFileName, const std::string &normalFileName);

		const sf::Texture &diffuseTexture() const override;
		const sf::Texture &normalTexture() const override;

	private:
		sf::Texture m_diffuseTexture;
		sf::Texture m_normalTexture;
};

class PlayerCharacterTextureProvider : public TextureProvider
{
	public:
		PlayerCharacterTextureProvider();
};

class EnemyTextureProvider : public TextureProvider
{
	public:
		EnemyTextureProvider();
};

#endif // ITEXTUREPROVIDER

