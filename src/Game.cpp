//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>
#include <Error.hpp>
#include <Player.hpp>
#include <ModelTexture.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SplashScreen.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Camera.hpp"

void Game::start()
{
	if (!_window.isInitialised())
		throw Error::CreateWindowError("Failed to initialize window");

	_gameState = Game::Playing;



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
	ModelTexture * texture = new ModelTexture("../assets/objects/mario_walking_2.obj");

	Player * player = new Player(*texture, 0, 0);
	player->setScale(0.2f);

	_gameObjectManager.add("player", player);

	sf::Clock clock;

	Shaders shader("_deps/graphics-src/Resources/VertexShaders/ShadedModelsVert.glsl",
			"_deps/graphics-src/Resources/FragmentShaders/ShadedModelsFrag.glsl");

	_camera.LookAt(glm::vec3(0));

	while(_gameState == Game::Playing)
	{
		_window.clear(0.5f, 0.5f, 0.5f);
		_camera.SetShaderView(shader, _window.Width(), _window.Height());

		shader.setVec3("light", glm::vec3(-30, 30, 30));
		_gameObjectManager.drawAll(shader);

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
Camera Game::_camera(glm::vec3(30.0f, 30.0f, 30.0f));
