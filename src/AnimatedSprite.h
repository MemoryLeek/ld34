#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/Sprite.hpp>

class AnimatedSpriteState;

class AnimatedSprite : public sf::Sprite
{
	public:
		AnimatedSprite(const sf::Texture& texture, AnimatedSpriteState &state);

		void update(float delta);

	private:
		AnimatedSpriteState &m_state;

};

#endif // ANIMATEDSPRITE_H
