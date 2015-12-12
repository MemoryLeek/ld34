#include <SFML/Graphics/Texture.hpp>

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: m_timePerFrame(0)
	, m_currentFrame(0)
	, m_numberOfFrames(0)
	, m_timeSinceLastFrameChange(0)
{
}

AnimatedSprite::AnimatedSprite(const sf::Texture &texture, int frameRate)
	: sf::Sprite(texture)
	, m_timePerFrame(1.f / frameRate)
	, m_currentFrame(0)
	, m_numberOfFrames(getTexture()->getSize().x / getTexture()->getSize().y)
	, m_timeSinceLastFrameChange(0)
{
}

void AnimatedSprite::update(float delta)
{
	if (m_timeSinceLastFrameChange > m_timePerFrame)
	{
		m_currentFrame = (m_currentFrame + 1 >= m_numberOfFrames) ? 0 : m_currentFrame + 1;
		m_timeSinceLastFrameChange -= m_timePerFrame;
	}
	m_timeSinceLastFrameChange += delta;

	const auto& size = getTexture()->getSize().y;
	setTextureRect(sf::IntRect(size * m_currentFrame, 0, size, size));
}
