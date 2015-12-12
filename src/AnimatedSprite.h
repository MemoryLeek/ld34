#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/Sprite.hpp>

class AnimatedSprite : public sf::Sprite
{
	public:
		AnimatedSprite();
		AnimatedSprite(const sf::Texture& texture, int frameRate);

		void update(float delta);

	private:
		float m_timePerFrame;
		int m_currentFrame;
		int m_numberOfFrames;

		float m_timeSinceLastFrameChange;

};

#endif // ANIMATEDSPRITE_H
