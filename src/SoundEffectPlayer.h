#ifndef SOUNDEFFECTPLAYER_H
#define SOUNDEFFECTPLAYER_H

#include <map>
#include <vector>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Vector2.hpp>

class SoundEffectPlayer
{
	public:
		enum class SoundEffect
		{
			Explosion,
			Cloning,
			Squish
		};

		SoundEffectPlayer();

		void play(SoundEffect effect, const sf::Vector2f& position);

	private:
		std::map<SoundEffect, sf::SoundBuffer> m_soundBuffers;
		std::vector<sf::Sound> m_soundEmitters;
};

#endif // SOUNDEFFECTPLAYER_H
