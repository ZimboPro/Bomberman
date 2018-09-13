//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>
#include <Error.hpp>
#include <Player.hpp>
#include <Model_Texture.hpp>
#include <Shaders.hpp>
#include <atomic>
#include <thread>
#include <chrono>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
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

	GameObjectManager::init();

	_gameState = Game::Playing;

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);


	loadKeys();
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
			showMenu();
			break;
		case Game::Exiting:
			break;
		case Game::ShowingOptions:
			showOptions();
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

void Game::showMenu()
{
	MainMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);

	if (selection == MainMenu::Exit)
		_gameState = Game::Exiting;
	else if (selection == MainMenu::Play)
		_gameState = Game::Playing;
	else if (selection == MainMenu::Settings)
		_gameState = Game::ShowingOptions;
}

void Game::showOptions()
{
	OptionsMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	if (selection == OptionsMenu::Back)
		_gameState = Game::ShowingMenu;
	else
		_gameState = Game::Exiting;
}

void Game::playGame()
{
	sf::Clock clock;

	Shaders shader("_deps/graphics-src/Resources/VertexShaders/ShadedModelsVert.glsl",
			"_deps/graphics-src/Resources/FragmentShaders/ShadedModelsFrag.glsl");

	_camera.LookAt(glm::vec3(0));

	while(_gameState == Game::Playing)
	{
		_window.clear(0.5f, 0.5f, 0.5f);
		_camera.SetShaderView(shader, _window.Width(), _window.Height());

		shader.setVec3("light", glm::vec3(-30, 30, 30));
		GameObjectManager::drawAll(shader);

		_window.update();

		GameObjectManager::updateAll(clock.getElapsedTime().asSeconds());
		clock.restart();

		if(_window.isKeyPressed(getKeyConfigured(eKeys::Escape)) || _window.closed())
			_gameState = Game::Exiting;
	}
	return ;
}

int Game::getKeyConfigured(eKeys key)
{
	return _keyConfiguration[key];
}

bool Game::setKeyConfigured(eKeys key, int keycode)
{
	std::map<eKeys, int>::iterator it;

	for ( it = _keyConfiguration.begin(); it != _keyConfiguration.end(); it++ )
	{
		if (it->second == keycode)
			return false;
	}

	_keyConfiguration[key] = keycode;
	return true;
}

void Game::loadKeys()
{
	_keyConfiguration[eKeys::Up] = GLFW_KEY_UP;
	_keyConfiguration[eKeys::Down] = GLFW_KEY_DOWN;
	_keyConfiguration[eKeys::Left] = GLFW_KEY_LEFT;
	_keyConfiguration[eKeys::Right] = GLFW_KEY_RIGHT;
	_keyConfiguration[eKeys::Select] = GLFW_KEY_ENTER;
	_keyConfiguration[eKeys::Pause] = GLFW_KEY_SPACE;
	_keyConfiguration[eKeys::Escape] = GLFW_KEY_ESCAPE;
}

eKeys Game::keyPressed()
{
	std::map<eKeys, int>::iterator it;

	for ( it = _keyConfiguration.begin(); it != _keyConfiguration.end(); it++ )
	{
		if (_window.isKeyPressed(it->second))
			return it->first;
	}
	return eKeys::Undefined;
}

eKeys Game::keyTyped()
{
	std::map<eKeys, int>::iterator it;

	for ( it = _keyConfiguration.begin(); it != _keyConfiguration.end(); it++ )
	{
		if (_window.isKeyTyped(it->second))
			return it->first;
	}
	return eKeys::Undefined;
}

Game::eGameState Game::_gameState = Game::Uninitialized;
Window Game::_window("Bomberman", 1024, 768);
int Game::_keyPress = 0;
Camera Game::_camera(glm::vec3(30.0f, 30.0f, 30.0f));
std::map<eKeys, int> Game::_keyConfiguration;
LoadingScreen Game::_loadingScreen;
Settings Game::_settings{eScreen::s1920, false, true, eVolume::v60, true};