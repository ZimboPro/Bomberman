//
// Created by Patrick RUSSELL on 2018/08/27.
//

#include "SFMLSoundProvider.hpp"

SFMLSoundProvider::SFMLSoundProvider()
{
	_sound.setVolume(100.0f);
}

void SFMLSoundProvider::playSound(std::string fileName)
{
	if(_soundBuffer.getDuration().asMilliseconds() == 0)
	{
		_soundBuffer.loadFromFile(fileName);
	}
	if(_sound.getStatus() == sf::SoundSource::Status::Playing)
	{
		_sound.stop();
	}
	_sound.setBuffer(_soundBuffer);
	_sound.play();
}

void SFMLSoundProvider::playSong(std::string fileName, bool looping)
{
	if(!_music.openFromFile(fileName))
		return ;
	_music.setLoop(looping);
	_music.play();
}

void SFMLSoundProvider::stopAllSounds()
{
	if (_sound.getStatus() == sf::SoundSource::Status::Playing)
		_sound.stop();
	if(_music.getStatus() == sf::SoundSource::Status::Playing)
		_music.stop();
}

bool SFMLSoundProvider::isSoundPlaying() const
{
	if(_sound.getStatus() == sf::SoundSource::Status::Playing)
		return true;
	return false;
}

bool SFMLSoundProvider::isSongPlaying() const
{
	if(_sound.getStatus() == sf::SoundSource::Status::Playing)
		return true;
	return false;
}
