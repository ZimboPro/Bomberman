//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SplashScreen.hpp"
#include "Player.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"

void Game::start()
{
	if (_gameState != Uninitialized)
		return;

	_window.create(sf::VideoMode(1024, 768), "Test");
	_gameState = Game::Playing;

	Player * player = new Player();
	player->Load("player");
	player->setPosition(1024 / 2, 758 / 2);

	_gameObjectManager.add("player", player);

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);

	while (!isExiting())
	{
		gameLoop();
	}

	_window.close();
}

sf::Vector2u Game::getWindowSize()
{
	return _window.getSize();
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
			ServiceLocator::getAudio()->playSong(../)
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
	sf::Clock clock;

	while(_gameState == Game::Playing)
	{
		_window.clear(sf::Color::Magenta);
		_gameObjectManager.drawAll(_window);
		_window.display();

		_gameObjectManager.updateAll(clock.getElapsedTime().asSeconds());
		clock.restart();

		if(_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				_gameState = Game::Exiting;
			}
			if(event.type == sf::Event::KeyPressed)
			{
				_keyPress = event.key.code;
			}
		}
	}
	return ;
}

int Game::getInput()
{
	return _keyPress;
}


Game::eGameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_window;
GameObjectManager Game::_gameObjectManager;
int Game::_keyPress = 0;
