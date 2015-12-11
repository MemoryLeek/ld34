#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Entity.h"

class Light : public sf::Drawable, public sf::Transformable
{
	public:
		Light(float radius, const sf::Texture& screenSpaceNormalMap, const std::vector<Entity*>& shadowCastingEntities, const sf::Color& color = sf::Color::White);

		float height() const;
		Light& setHeight(float height);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		const float m_radius;
		const sf::Texture& m_screenSpaceNormalMap;
		const std::vector<Entity*>& m_shadowCastingEntities;
		sf::Color m_color;
		float m_height;

		sf::Shader m_shadowMapShader;
		sf::Shader m_lightMapShader;
		mutable sf::RenderTexture m_occlusionMap;
		mutable sf::RenderTexture m_shadowMap;
		mutable sf::RenderTexture m_normalMap;

		sf::VertexArray m_occlusionMapRect;
		sf::VertexArray m_shadowMapRect;
		sf::VertexArray m_normalMapRect;
};

#endif // LIGHT_H
