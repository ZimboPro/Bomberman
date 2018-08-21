//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "MainMenu.hpp"
#include <iostream>


MainMenu::MenuResult MainMenu::show(sf::RenderWindow &window)
{
	sf::Texture texture;
	if(!texture.loadFromFile("../assets/mainmenu.png"))
		return MainMenu::Exit;

	sf::Sprite sprite(texture);

	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = playButton.rect.top + 380;
	playButton.rect.left = 0;
	playButton.rect.width = playButton.rect.left + 1023;
	playButton.action = MainMenu::Play;


	MenuItem exitButton;
	exitButton.rect.top = 0;
	exitButton.rect.height = exitButton.rect.top + 1023;
	exitButton.rect.left = 380;
	exitButton.rect.width= exitButton.rect.left + 560;
	exitButton.action = MainMenu::Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return (getMenuResponse(window));
}

MainMenu::MenuResult  MainMenu::handleClick(int x, int y)
{
	for(auto menuItem : _menuItems)
	{
		if (y >= menuItem.rect.top && y <= (menuItem.rect.top + menuItem.rect.height))
			if (x >= menuItem.rect.left && y <= (menuItem.rect.left + menuItem.rect.width))
			{
				std::cout << "Returning form handleClick" << std::endl;

				return menuItem.action;
			}
	}
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow &window)
{
	sf::Event event;

	while(window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					return MenuResult::Exit;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
						return handleClick(event.mouseButton.x, event.mouseButton.y);
				default:
					break;
			}
		}
	}
}