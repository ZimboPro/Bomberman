//
// Created by Patrick RUSSELL on 2018/08/27.
//

#include "Error.hpp"
#include "SFMLSoundProvider.hpp"

SFMLSoundProvider::SFMLSoundProvider(): _currentSongName("")
{
}

void SFMLSoundProvider::playSound(std::string fileName)
{
	int availChannel = -1;

	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() == sf::Sound::Playing)
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
			_currentSounds[availChannel].play();
		}
		catch (std::exception & e)
		{
			std::stderr << e.what() << std::endl;
		}
	}
}

void SFMLSoundProvider::playSong(std::string fileName, bool looping)
{
	sf::Music * currentSong;

	try
	{
		currentSong = _soundFileCache.getSong(fileName);
	}
	catch (std::exception & e)
	{
		std::stderr << e.what() << std::endl;
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
			std::stderr << e.what() << std::endl;
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

bool SFMLSoundProvider::isSoundPlaying() const
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
		if(_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;

	return false;
}

bool SFMLSoundProvider::isSongPlaying() const
{
	if(_currentSongName != "")
		return _soundFileCache.getSong(_currentSongName).getStatus() == sf::Sound::Playing;
	return false;
}
