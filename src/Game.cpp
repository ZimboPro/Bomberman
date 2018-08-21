//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <MainMenu.hpp>
#include <iostream>
#include "Game.hpp"
#include "SplashScreen.hpp"

void Game::start()
{
    if (_gameState != Uninitialized)
        return;

    _window.create(sf::VideoMode(1024, 768), "Test");
    _gameState = Game::ShowingSplash;

    while (!isExiting())
    {
        gameLoop();
    }

    _window.close();
}

bool Game::isExiting()
{
    if (_gameState == Game::Exiting)
        return true;
    return false;
}

void Game::gameLoop()
{
    sf::Event event;
    SplashScreen splash;
    MainMenu menu;

    while(_window.pollEvent(event))
    {
        switch(_gameState)
        {
        	case Game::Playing:
        		_window.clear(sf::Color::Magenta);
        		_window.display();
        		if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        			_gameState = Game::Exiting;
        		break;
			case Game::ShowingSplash:
				splash.show(_window);
				_gameState = Game::ShowingMenu;
				break;
			case Game::Paused:break;
			case Game::ShowingMenu:
				menu.show((_window));
				_gameState = Game::Playing;
			case Game::Exiting:break;
			default:break;
		}
    }
}

Game::eGameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_window;

