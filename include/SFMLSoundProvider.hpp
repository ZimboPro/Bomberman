//
// Created by Patrick RUSSELL on 2018/08/27.
//

#ifndef BOMBERMAN_SFMLSOUNDPROVIDER_HPP
#define BOMBERMAN_SFMLSOUNDPROVIDER_HPP

#include "IAudioProvider.hpp"
#include <SFML/Audio.hpp>

class SFMLSoundProvider: public IAudioProvider
{
public:
	SFMLSoundProvider();

	void playSound(std::string fileName);
	void playSong(std::string fileName, bool looping);
	void stopAllSounds();

	bool isSoundPlaying() const;
	bool isSongPlaying() const;

private:
	sf::SoundBuffer _soundBuffer;
	sf::Sound _sound;
	sf::Music _music;
};

#endif //BOMBERMAN_SFMLSOUNDPROVIDER_HPP
