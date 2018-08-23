//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <SFML/Graphics.hpp>
#include "SplashScreen.hpp"
#include "Game.hpp"

void SplashScreen::show(sf::RenderWindow & window)
{
	sf::Texture texture;
	if(!texture.loadFromFile("../assets/Splashscreen.png"))
		return ;

	sf::Sprite sprite(texture);

	window.draw(sprite);
	window.display();

	sf::Event event;
	while(window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed ||
				event.type == sf::Event::EventType::MouseButtonPressed ||
				event.type == sf::Event::EventType::Closed)
				return;
		}
	}
}
