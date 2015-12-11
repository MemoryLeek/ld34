#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
	public:
		Entity(const sf::Texture& diffuseTexture, const sf::Texture& normalTexture);

		void drawNormalMapTo(sf::RenderTarget &target, sf::RenderStates states) const;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		const sf::Texture& m_diffuseTexture;
		const sf::Texture& m_normalTexture;
		mutable sf::Shader m_normalMapRotationShader;
};

#endif // ENTITY_H
