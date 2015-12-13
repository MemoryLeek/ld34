#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TextOverlay.h"
#include "Util.h"

TextOverlay::TextOverlay(const std::string &mainText, const std::string &subText)
	: m_mainText(mainText)
	, m_subText(subText)
	, m_timer(0)
{
	m_font.loadFromFile("fonts/oxygen.ttf");
}

void TextOverlay::update(float delta)
{
	m_timer += delta;
}

void TextOverlay::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const auto alpha = std::min(m_timer / 1.0f, 1.0f);

	sf::Color textColor(255, 255, 255, alpha * 255.0f);

	sf::Text deathText1(m_mainText, m_font);
	deathText1.setCharacterSize(50);
	deathText1.setStyle(sf::Text::Bold);
	deathText1.setColor(textColor);

	sf::Text deathText2(m_subText, m_font);
	deathText2.setCharacterSize(20);
	deathText2.setColor(textColor);

	const auto &windowSize = target.getSize();
	const auto &textBounds1 = deathText1.getLocalBounds();
	const auto &textBounds2 = deathText2.getLocalBounds();

	deathText1.setPosition((windowSize.x - textBounds1.width) / 2, (windowSize.y - textBounds1.height) / 2);
	deathText2.setPosition((windowSize.x - textBounds2.width) / 2, (windowSize.y - textBounds2.height) / 2 + 60);

	const auto &defaultView = target.getDefaultView();

	sf::RectangleShape overlay;
	overlay.setSize((sf::Vector2f)windowSize);
	overlay.setFillColor(sf::Color(0, 0, 0, alpha * 150));

	target.setView(defaultView);
	target.draw(overlay);
	target.draw(deathText1);
	target.draw(deathText2);
}

