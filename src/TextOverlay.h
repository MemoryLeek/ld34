#ifndef TEXTOVERLAY_H
#define TEXTOVERLAY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>

class TextOverlay : public sf::Drawable
{
	public:
		TextOverlay(const std::string &mainText, const std::string &subText);

		void update(float delta);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		std::string m_mainText;
		std::string m_subText;

		sf::Font m_font;

		float m_timer;
};

#endif // TEXTOVERLAY_H
