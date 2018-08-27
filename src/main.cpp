#include <iostream>
#include "Game.hpp"
#include "SFMLSoundProvider.hpp"


int main()
{
	//Game::start();
	SFMLSoundProvider sound;

	sound.playSong("../assets/sounds/background_music/level_one.wav", false);
	sound.playSound("../assets/sounds/gameplay/death.wav");

	while(true) {}

	return 0;
}
