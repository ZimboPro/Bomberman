/*#include <iostream>
#include "Game.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"


int main()
{
	Game::start();

	return 0;
}
*/
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Resize ,settings);
	window.setVerticalSyncEnabled(true);

	// activate the window
	window.setActive(true);

	settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	// load resources, initialize the OpenGL states, ...

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}
