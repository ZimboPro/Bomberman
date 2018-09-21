//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include <iostream>
#include <Error.hpp>
#include <game_elements/Player.hpp>
#include <Model_Texture.hpp>
#include <Shaders.hpp>
#include <atomic>
#include <thread>
#include <chrono>

#include "Game.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/OptionsMenu.hpp"
#include "Menus/PauseMenu.hpp"
#include "SplashScreen.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"
#include "Menus/StartGameMenu.hpp"
#include "Map.hpp"
#include "game_elements/Player.hpp"
#include "Camera.hpp"
#include "GameInterface.hpp"

Game::Game() {}

Game::Game(Game const & src) 
{
	*this = src;
}

Game::~Game() {}

void Game::start()
{
	if (!_window.isInitialised())
		throw Error::CreateWindowError("Failed to initialize window");

	// GameObjectManager::init();
	_loadingScreen.loadModels();
	_interface.loadObjects();

	_gameState = Game::ShowingMenu;

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);


	loadKeys();
	while (!isExiting())
	{
		gameLoop();
	}
	_interface.deleteObjects();
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
			showPauseMenu();
			break;
		case Game::ShowingMenu:
			showMenu();
			break;
		case Game::Exiting:
			break;
		case Game::ShowingOptions:
			showOptions();
			break;
		case Game::ShowingStartGameMenu:
			showStartGameMenu();
			break;
		default:
			break;
	}
}

void Game::showPauseMenu()
{
	PauseMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	if (selection == PauseMenu::Quit)
		_gameState = Game::ShowingMenu;
}

void Game::showStartGameMenu()
{
	StartGameMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	if (selection == StartGameMenu::Back)
		_gameState = Game::ShowingMenu;
}

void Game::showSplashScreen()
{
	Shaders shader("../assets/shaders/vert/SpriteVert.glsl", "../assets/shaders/frag/SpriteFrag.glsl");

	SplashScreen splash;
	splash.show(shader, "../assets/images/intro/");
	_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);

	if (selection == MainMenu::Exit)
		_gameState = Game::Exiting;
	else if (selection == MainMenu::Play)
		// _gameState = Game::ShowingStartGameMenu;
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
}

void Game::playGame()
{
	sf::Clock clock;

	Shaders shader("_deps/graphics-src/Resources/VertexShaders/ShadedModelsVert.glsl",
			"_deps/graphics-src/Resources/FragmentShaders/ShadedModelsFrag.glsl");

	_camera.LookAt(glm::vec3(0));

	_interface.resetHOD();
	_interface.resetTime(70);
	_interface.resetPostions();

	while(_gameState == Game::Playing)
	{
		_window.clear(0.5f, 0.5f, 0.5f);
		_camera.SetShaderView(shader, _window.Width(), _window.Height());

		shader.setVec3("light", glm::vec3(-30, 30, 30));
		// GameObjectManager::drawAll(shader);
		_interface.display();
		_window.update();

		// GameObjectManager::updateAll(clock.getElapsedTime().asSeconds());
		clock.restart();
		if (keyTyped() == eKeys::Up)
			_interface.adjustLives(1);
		if (keyTyped() == eKeys::Down)
			_interface.adjustLives(-1);
		if (keyTyped() == eKeys::Right)
			_interface.adjustScore(10);
		if (keyTyped() == eKeys::Left)
			_interface.adjustScore(-5);

		if(_window.isKeyPressed(getKeyConfigured(eKeys::Escape)) || _window.closed() || _interface.timerEnded() || !_interface.stillAlive())
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
	_keyConfiguration[eKeys::Select] = GLFW_KEY_ENTER;
	_keyConfiguration[eKeys::Place] = GLFW_KEY_SPACE;
	_keyConfiguration[eKeys::Escape] = GLFW_KEY_ESCAPE;
	if (Game::_KeyBind == false) 
	{
		_keyConfiguration[eKeys::Up] = GLFW_KEY_UP;
		_keyConfiguration[eKeys::Down] = GLFW_KEY_DOWN;
		_keyConfiguration[eKeys::Left] = GLFW_KEY_LEFT;
		_keyConfiguration[eKeys::Right] = GLFW_KEY_RIGHT;
	}
	else
	{
		_keyConfiguration[eKeys::Up] = GLFW_KEY_W;
		_keyConfiguration[eKeys::Down] = GLFW_KEY_S;
		_keyConfiguration[eKeys::Left] = GLFW_KEY_A;
		_keyConfiguration[eKeys::Right] = GLFW_KEY_D;
	}
}

void Game::loadSettings()
{
	switch (Game::_settings.size)
	{
		case s1024:
			Game::_window.resize(1024, 768);
			break;
		case s1280:
			Game::_window.resize(1280, 720);
			break;
		case s1920:
			Game::_window.resize(1920, 1080);
			break;
	}
	if (Game::_settings.fullscreen)
		Game::_window.fullscreen();
	else
		Game::_window.windowed();
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
Camera Game::_camera(glm::vec3(15.0f, 15.0f, 15.0f));
std::map<eKeys, int> Game::_keyConfiguration;
LoadingScreen Game::_loadingScreen;
Settings Game::_settings{eScreen::s1920, false, true, eVolume::v60, true};
bool Game::_KeyBind = false;