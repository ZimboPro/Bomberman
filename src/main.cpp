#include <iostream>
#include "Map.hpp"
#include "Game.hpp"


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
	catch (std::logic_error & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
