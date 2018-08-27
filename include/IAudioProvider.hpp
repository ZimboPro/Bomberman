//
// Created by Patrick RUSSELL on 2018/08/27.
//

#ifndef BOMBERMAN_IAUDIOPROVIDER_HPP
#define BOMBERMAN_IAUDIOPROVIDER_HPP

class IAudioProvider
{
public:
	virtual ~IAudioProvider() {}
	virtual void playSound(std::string fileName) = 0;
	virtual void playSong(std::string fileName, bool looping) = 0;
	virtual void stopAllSounds() = 0;

	virtual bool isSoundPlaying() const = 0;
	virtual bool isSongPlaying() const = 0;
};

#endif //BOMBERMAN_IAUDIOPROVIDER_HPP
