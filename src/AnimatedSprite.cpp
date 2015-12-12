#include <SFML/Graphics/Texture.hpp>

#include "AnimatedSprite.h"
#include "AnimatedSpriteState.h"

AnimatedSprite::AnimatedSprite(const sf::Texture &texture, AnimatedSpriteState &state)
	: sf::Sprite(texture)
	, m_state(state)
{

}

void AnimatedSprite::update(float delta)
{
	if (m_state.m_timeSinceLastFrameChange > m_state.m_timePerFrame)
	{
		m_state.m_current = (m_state.m_current + 1 >= m_state.m_end) ? m_state.m_start : m_state.m_current + 1;
		m_state.m_timeSinceLastFrameChange -= m_state.m_timePerFrame;
	}
	m_state.m_timeSinceLastFrameChange += delta;

	const auto& size = getTexture()->getSize().y;
	setTextureRect(sf::IntRect(size * m_state.m_current, 0, size, size));
}
