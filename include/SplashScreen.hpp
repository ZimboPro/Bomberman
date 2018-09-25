//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_SPLASHSCREEN_HPP
#define BOMBERMAN_SPLASHSCREEN_HPP

#include <TextureImages.hpp>
#include <vector>

class Shaders;

class SplashScreen
{
	public:
		SplashScreen();
		SplashScreen(SplashScreen const & src);
		~SplashScreen();
		void show(Shaders & shader, std::string file, int number);
	private:
		float _fps;
		float _timePerFPS;
		float _time;
};

#endif //BOMBERMAN_SPLASHSCREEN_HPP
