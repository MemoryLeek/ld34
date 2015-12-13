#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Character.h"
#include "LightContext.h"

namespace Tiled
{
	class Map;
}

class Light : public sf::Drawable, public sf::Transformable
{
	public:
		Light(const LightContext& context, float radius, const sf::Color& color = sf::Color::White);

		float height() const;
		Light& setHeight(float height);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		const LightContext& m_context;
		const float m_radius;
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
