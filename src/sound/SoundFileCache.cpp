//
// Created by Patrick RUSSELL on 2018/08/29.
//


#include <algorithm>
#include <iostream>
#include "Error.hpp"
#include "sound/SoundFileCache.hpp"

SoundFileCache::SoundFileCache() {}

SoundFileCache::SoundFileCache(SoundFileCache const & src) 
{
	*this = src;
}

SoundFileCache::~SoundFileCache()
{
	std::for_each(_sounds.begin(), _sounds.end(), SoundDeallocator());
	std::for_each(_music.begin(), _music.end(), MusicDeallocator());
}

sf::Sound SoundFileCache::getSound(const std::string & filename)
{
	auto result = _sounds.find(filename);
	if(result == _sounds.end())
	{
		auto * soundBuffer = new sf::SoundBuffer;

		if(!soundBuffer->loadFromFile(filename))
			throw (Error::AssetError("Asset " + filename + " not found"));
		_sounds.insert(std::make_pair(filename, soundBuffer));
		sf::Sound sound(*soundBuffer);
		return sound;
	}
	else
	{
		sf::Sound sound(*(result->second));
		return sound;
	}
}

sf::Music * SoundFileCache::getSong(const std::string & filename)
{
	auto result = _music.find(filename);
	if(result == _music.end())
	{
		auto * music = new sf::Music;
		if(!music->openFromFile(filename))
			throw (Error::AssetError("Asset " + filename + " not found"));
		_music.insert(std::make_pair(filename, music));
		return music;
	}
	else
	{
		return result->second;
	}
}

void SoundFileCache::SoundDeallocator::operator()(const std::pair<std::string, sf::SoundBuffer *> & p)
{
	delete p.second;
}

void SoundFileCache::MusicDeallocator::operator()(const std::pair<std::string, sf::Music *> & p)
{
	delete p.second;
}

std::map<std::string, sf::SoundBuffer *> SoundFileCache::_sounds;
std::map<std::string, sf::Music *> SoundFileCache::_music;
