#ifndef CREDITS_HPP
#define CREDITS_HPP

#include "ServiceLocator.hpp"
#include <TextureImages.hpp>
#include <vector>

class Shaders;

class Credits
{
	public:
		Credits();
		Credits(Credits const & src);
		~Credits();
		void show(Shaders & shader, std::string file);
	private:
		float _fps;
		float _timePerFPS;
		float _time;
        IAudioProvider * _sound;
};

#endif