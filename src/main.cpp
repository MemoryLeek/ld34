#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "Light.h"
#include "tiled/Map.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld34");

	sf::RenderTexture lightBuffer;
	lightBuffer.create(window.getSize().x, window.getSize().y);

	sf::RenderTexture normalMapFbo;
	normalMapFbo.create(window.getSize().x, window.getSize().y);

	Tiled::Map map("maps/1.json");
	Light mouseLight(512, normalMapFbo.getTexture(), sf::Color::White);

	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseWorldPosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					mouseWindowPosition.x = event.mouseMove.x;
					mouseWindowPosition.y = event.mouseMove.y;
					mouseWorldPosition = window.mapPixelToCoords(mouseWindowPosition);

					mouseLight.setPosition(mouseWorldPosition);
					break;
				case sf::Event::MouseWheelScrolled:
					if (event.mouseWheel.x > 0)
					{
						mouseLight.setHeight(mouseLight.height() - 0.05f);
					}
					else
					{
						mouseLight.setHeight(mouseLight.height() + 0.05f);
					}
					break;
				default:
					break;
			}
		}

		window.clear(sf::Color::White);

		// Step 0 - Draw the map normals to the normal map FBO
		normalMapFbo.clear(sf::Color(127, 127, 255)); // Make the empty background face us
		map.drawBackgroundNormalMapTo(normalMapFbo, sf::BlendAlpha);
		normalMapFbo.display();

		// Step 1 - Draw everything that should receive light
		window.draw(map);

		// Step 2 - Draw all lights to the light buffer
		lightBuffer.clear(sf::Color(100, 100, 100)); // Ambient color
		// Draw all lights (BlendAdd) to the light buffer
		lightBuffer.draw(mouseLight);
		lightBuffer.display();

		// Step 3 - Draw the light buffer to the screen with BlendMultiply
		sf::Sprite lightMapSprite(lightBuffer.getTexture());
		window.draw(lightMapSprite, sf::BlendMultiply);

		// Step 4 - Draw everything that doesn't receive light


		window.display();
	}

	return 0;
}
