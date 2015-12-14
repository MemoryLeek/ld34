#include "SoundEffectPlayer.h"

SoundEffectPlayer::SoundEffectPlayer()
{
	m_soundBuffers[SoundEffect::Explosion].loadFromFile("sfx/bomb.wav");
	m_soundBuffers[SoundEffect::Cloning].loadFromFile("sfx/clone.wav");
	m_soundBuffers[SoundEffect::Squish].loadFromFile("sfx/squish.wav");
	m_soundBuffers[SoundEffect::Grow].loadFromFile("sfx/grow.wav");
	m_soundBuffers[SoundEffect::Shrink].loadFromFile("sfx/shrink.wav");
}

void SoundEffectPlayer::play(SoundEffectPlayer::SoundEffect effect, const sf::Vector2f &position)
{
	// Re-use Sound players if we have a free one
	for (auto& sound : m_soundEmitters)
	{
		if (sound.getStatus() == sf::SoundSource::Stopped)
		{
			sound.setBuffer(m_soundBuffers[effect]);
			sound.setPosition(position.x, position.y, 0);
			sound.play();
			return;
		}
	}

	// Otherwise we add a new emitter
	m_soundEmitters.push_back(sf::Sound(m_soundBuffers[effect]));
	m_soundEmitters.back().setAttenuation(0.01f);
	m_soundEmitters.back().setPosition(position.x, position.y, 0);
	m_soundEmitters.back().play();
}
