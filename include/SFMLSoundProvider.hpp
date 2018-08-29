//
// Created by Patrick RUSSELL on 2018/08/27.
//

#ifndef BOMBERMAN_SFMLSOUNDPROVIDER_HPP
#define BOMBERMAN_SFMLSOUNDPROVIDER_HPP

#include "IAudioProvider.hpp"
#include "SoundFileCache.hpp"
#include <SFML/Audio.hpp>

class SFMLSoundProvider: public IAudioProvider
{
public:
	SFMLSoundProvider();

	void playSound(std::string fileName);
	void playSong(std::string fileName, bool looping);
	void stopAllSounds();

	bool isSoundPlaying();
	bool isSongPlaying();

private:
	static const int MAX_SOUND_CHANNELS= 10;

	SoundFileCache _soundFileCache;
	sf::Sound _currentSounds[MAX_SOUND_CHANNELS];
	std::string _currentSongName;
};

#endif //BOMBERMAN_SFMLSOUNDPROVIDER_HPP