//
// Created by Patrick RUSSELL on 2018/08/27.
//

#include <iostream>
#include "Error.hpp"
#include "sound/SFMLSoundProvider.hpp"

SFMLSoundProvider::SFMLSoundProvider(): _currentSongName(""), _level(100)
{
}

SFMLSoundProvider::SFMLSoundProvider(SFMLSoundProvider const & src) 
{
	*this = src;
}

void SFMLSoundProvider::setSoundLevel(float level)
{
	_level = level;
}


SFMLSoundProvider::~SFMLSoundProvider() {}

void SFMLSoundProvider::playSound(std::string fileName)
{
	int availChannel = -1;

	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availChannel = i;
			break ;
		}
	}
	if(availChannel != -1)
	{
		try
		{
			_currentSounds[availChannel] = _soundFileCache.getSound(fileName);
			_currentSounds[availChannel].setVolume(_level);
			_currentSounds[availChannel].play();
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	if(availChannel == -1)
		;
		// std::cout << "No chanel found" << std::endl;
}

void SFMLSoundProvider::playSong(std::string fileName, bool looping)
{
	sf::Music * currentSong;

	try
	{
		currentSong = _soundFileCache.getSong(fileName);
		currentSong->setVolume(_level >> 1);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return ;
	}

	if(_currentSongName != "")
	{
		try
		{
			sf::Music * priorSong = _soundFileCache.getSong(fileName);
			if(priorSong->getStatus() != sf::Sound::Stopped)
				priorSong->stop();
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	_currentSongName = fileName;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::stopAllSounds()
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].stop();
	}
	if(_currentSongName != "")
	{
		sf::Music * currentSong = _soundFileCache.getSong(_currentSongName);
		if(currentSong->getStatus() == sf::Sound::Playing)
			currentSong->stop();
	}
}

bool SFMLSoundProvider::isSoundPlaying()
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
		if(_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	return false;
}

bool SFMLSoundProvider::isSongPlaying()
{
	if(_currentSongName != "" && _soundFileCache.getSong(_currentSongName)->getStatus() == sf::Sound::Playing)
		return true;
	return false;
}
