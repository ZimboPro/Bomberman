#include <iostream>
#include "Game.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"


int main()
{
	try
	{
		Game::start();
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
