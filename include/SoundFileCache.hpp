//
// Created by Patrick RUSSELL on 2018/08/29.
//

#ifndef BOMBERMAN_SOUNDFILECACHE_HPP
#define BOMBERMAN_SOUNDFILECACHE_HPP

#include <SFML/Audio.hpp>
#include <map>

class SoundFileCache {
public:
    SoundFileCache();
    SoundFileCache(SoundFileCache const & src);
    ~SoundFileCache();

    sf::Sound getSound(const std::string & filename);
    sf::Music * getSong(const std::string & filename);

private:
    static std::map<std::string, sf::SoundBuffer *> _sounds;
    static std::map<std::string, sf::Music *> _music;

    struct SoundDeallocator
    {
        void operator()(const std::pair<std::string, sf::SoundBuffer *> & p);
    };

    struct MusicDeallocator
    {
        void operator()(const std::pair<std::string, sf::Music *> & p);
    };

};


#endif //BOMBERMAN_SOUNDFILECACHE_HPP
