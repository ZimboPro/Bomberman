//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SplashScreen.hpp"

void Game::start()
{
	if (_gameState != Uninitialized)
		return;

	_window.create(sf::VideoMode(1024, 768), "Test");
	_gameState = Game::Playing;

	_player.Load("player");
	_player.setPosition(1024 / 2, 758 / 2);

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
	switch (_gameState)
	{
		case Game::Playing:
			playGame();
			break;
		case Game::ShowingSplash:
			showSplashScreen();
			break;
		case Game::Paused:
			break;
		case Game::ShowingMenu:
			showMenu();
			break;
		case Game::Exiting:
			break;
		default:
			break;
	}
}

void Game::showSplashScreen()
{
	SplashScreen splash;
	splash.show(_window);
	_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu menu;
	int selection = menu.show(_window);

	if (selection == MainMenu::Exit)
		_gameState = Game::Exiting;
	else if (selection == MainMenu::Play)
		_gameState = Game::Playing;
}

void Game::playGame()
{
	sf::Event event;

	while(_gameState == Game::Playing)
	{
		while (_window.pollEvent(event))
		{
			_window.clear(sf::Color::Magenta);
			_player.Draw(_window);
			_window.display();

			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				_gameState = Game::Exiting;
			}
		}
	}
	return ;
}

Game::eGameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_window;
Player Game::_player;
