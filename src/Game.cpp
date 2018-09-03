//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>
#include <Error.hpp>
#include <Player.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SplashScreen.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"
#include "Map.hpp"
#include "VisibleGameObject.hpp"

void Game::start()
{
	if (!_window.isInitialised())
		throw Error::CreateWindowError("Failed to initialize window");

	_gameState = Game::Playing;

//	Player * player = new Player();
//	player->Load("player");
//	player->setPosition(_window.Width() / 2, _window.Height() / 2);
//	player->setPosition(0, 0);

//	_gameObjectManager.add("player", player);

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);


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
//			showSplashScreen();
			break;
		case Game::Paused:
			break;
		case Game::ShowingMenu:
//			showMenu();
			break;
		case Game::Exiting:
			break;
		default:
			break;
	}
}

//void Game::showSplashScreen()
//{
//	SplashScreen splash;
//	splash.show(_window);
//	_gameState = Game::ShowingMenu;
//}

//void Game::showMenu()
//{
//	MainMenu menu;
//	int selection = menu.show(_window);
//
//	if (selection == MainMenu::Exit)
//		_gameState = Game::Exiting;
//	else if (selection == MainMenu::Play)
//		_gameState = Game::Playing;
//}

void Game::playGame()
{
//	sf::Event event;
	sf::Clock clock;

	while(_gameState == Game::Playing)
	{
		_window.clear(0.5f, 0.5f, 0.5f);
//		_gameObjectManager.drawAll(_window);
		_window.update();

		_gameObjectManager.updateAll(clock.getElapsedTime().asSeconds());
		clock.restart();

		if(_window.isKeyPressed(GLFW_KEY_ESCAPE) || _window.closed())
			_gameState = Game::Exiting;

	}
	return ;
}

int Game::getInput()
{
	return _keyPress;
}

Game::eGameState Game::_gameState = Game::Uninitialized;
GameObjectManager Game::_gameObjectManager;
Window Game::_window("Bomberman", 1024, 768);
int Game::_keyPress = 0;
