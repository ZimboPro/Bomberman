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
#include "Menus/LevelSelectMenu.hpp"
#include "SplashScreen.hpp"
#include "sound/SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"
#include "Menus/StartGameMenu.hpp"
#include "Map.hpp"
#include "game_elements/Player.hpp"
#include "map_generation/Levels.hpp"
#include "Camera.hpp"
#include "GameInterface.hpp"
#include "Screens/GameOver.hpp"
#include "Screens/GameWon.hpp"
#include "Screens/LevelPassed.hpp"
#include "Screens/Credits.hpp"

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

	_loadingScreen.loadModels();
	_interface.loadObjects();
	_camera.Zoom = 30.0f;

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
		case Game::ShowingLevelSelect:
			showLevelSelect();
			break;
		case Game::LostLevel:
			lostLevel();
			break;
		case Game::WonLevel:
			wonLevel();
		default:
			break;
	}
}

void Game::wonLevel()
{
	LevelPassed levelPassed;

	levelPassed.show();
	_startLevel += 1;
	_interface.setLevelCompleted(false);
	_gameState = Playing;
}

void Game::lostLevel()
{
	GameOver gameover;

	gameover.show();
	_gameState = ShowingMenu;
}

void Game::showPauseMenu()
{
	PauseMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	if (selection == PauseMenu::Quit)
	{
		GameObjectManager::clearObjects();
		_gameState = ShowingMenu;
	}
	if (selection == PauseMenu::Save)
		save();
}

void Game::showStartGameMenu()
{
	StartGameMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	if (selection == StartGameMenu::Start)
		_gameState = Game::ShowingLevelSelect;
	if (selection == StartGameMenu::Load)
		load();
	if (selection == StartGameMenu::Back)
		_gameState = Game::ShowingMenu;
}

void Game::showSplashScreen()
{
	Shaders shader("../assets/shaders/vert/SpriteVert.glsl", "../assets/shaders/frag/SpriteFrag.glsl");

	SplashScreen splash;
	splash.show(shader, "../assets/images/intro/", 238);
	_gameState = Game::ShowingMenu;
}

void Game::showLevelSelect()
{
	LevelSelectMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	std::cout << selection << std::endl;
	switch(selection)
	{
		case LevelSelectMenu::Random:
			Game::_startLevel = 0;
			_gameState = Playing;
			break;
		case LevelSelectMenu::lvl1:
			Game::_startLevel = 1;
			_gameState = Playing;
			break;
		case LevelSelectMenu::lvl2:
			Game::_startLevel = 2;
			_gameState = Playing;
			break;
		case LevelSelectMenu::lvl3:
			Game::_startLevel = 3;
			_gameState = Playing;
			break;
		case LevelSelectMenu::Back:
			_gameState = ShowingStartGameMenu;		
			break;
	}
	std::cout << Game::_startLevel << std::endl;
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
		_gameState = Game::ShowingStartGameMenu;
		// _gameState = Game::Playing;
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
	GameObjectManager::init();
	GameObjectManager::newLevel(Game::_startLevel);
	sf::Clock clock;

	Shaders shader("_deps/graphics-src/Resources/VertexShaders/ShadedModelsVert.glsl",
			"_deps/graphics-src/Resources/FragmentShaders/ShadedModelsFrag.glsl");

	_camera.LookAt(glm::vec3(0));


	_interface.resetHOD();
	_interface.resetTime(300);
	_interface.resetPostions();

	while(_gameState == Game::Playing)
	{
		_window.clear(0.2588f, 0.7961f, 0.8196f);
		_camera.SetShaderView(shader, _window.Width(), _window.Height());

		shader.setVec3("light", glm::vec3(-30, 30, 30));
		GameObjectManager::drawAll(shader);
		_interface.display();
		_window.update();

		GameObjectManager::updateAll(clock.getElapsedTime().asSeconds());
		clock.restart();

		// if (_window.isKeyPressed(getKeyConfigured(eKeys::Save)))
		// {
		// 	std::cout << "Q is pressed to save game\n";
		// 	save();
		// 	_gameState = Game::Exiting;
		// }
		// if (_window.isKeyPressed(getKeyConfigured(eKeys::Load)))
		// {
		// 	std::cout << "W is pressed to load game\n";
		// 	load();
		// 	_gameState = Game::Exiting;
		// }

		if(_window.isKeyPressed(getKeyConfigured(eKeys::Escape)))
		{
			float timeLeft = GameInterface::TimeLeft();
			showPauseMenu();
			GameInterface::resetTime(timeLeft);
		}
		if (_interface.timerEnded() || !_interface.stillAlive())
			_gameState = Game::LostLevel;

		if (_interface.completedLevel())
			_gameState = Game::WonLevel;

		if (_window.closed())
			_gameState = ShowingMenu;
	}
	return ;
}

void Game::showCredits()
{
	Shaders shader("../assets/shaders/vert/SpriteVert.glsl", "../assets/shaders/frag/SpriteFrag.glsl");

	SplashScreen splash;
	splash.show(shader, "../../Assets/credits/", 222);
	_gameState = Game::ShowingMenu;
}

void Game::save()
{
	int width = Map::width();
	int	height = Map::height();

	std::vector<std::vector<char> > saveMap(height, std::vector<char>(width, '0'));
	std::vector<std::vector<char> > loadedMap;


	// Map::printMap();
	std::cout << "====================Saved Map========================\n";
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (Map::at(x, y) == '1' || Map::at(x, y) == '2')
			{
				saveMap[y][x] = '1';
			}
			std::cout << saveMap[y][x];
		}
		std::cout << '\n';
	}
	std::cout << "======================================================\n";
	std::cout << "==============Original================================\n";

	Map::printMap();
	std::cout << "======================================================\n";
	// std::cout << "Saving\n";
	Map::_levels.save(saveMap, 2,3, 0);
	loadedMap = Map::_levels.load();

	std::cout << "Loaded Map\n";
	std::cout << loadedMap.size();
	std::cout << "\n======================================================\n";

	for (int i = 0; i < loadedMap.size(); i++)
	{
		for (int j = 0; j < loadedMap[i].size(); j++)
		{
			std::cout << loadedMap[i][j];
		}
		std::cout << '\n';
	}
		std::cout << "======================================================\n";

}

void Game::load()
{
	std::cout << "Not implemented" << std::endl;
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

	//Assigning save and load to 'q' and 'w' buttons

	_keyConfiguration[eKeys::Save] = GLFW_KEY_Q;
	_keyConfiguration[eKeys::Load] = GLFW_KEY_W;
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

void	Game::setGameStateGameWon()
{
	_gameState = ShowingMenu;
}

Game::eGameState Game::_gameState = Game::Uninitialized;
Window Game::_window("Bomberman", 1024, 768);
Camera Game::_camera(glm::vec3(15.0f, 25.0f, 0.0f));
std::map<eKeys, int> Game::_keyConfiguration;
LoadingScreen Game::_loadingScreen;
Settings Game::_settings{eScreen::s1024, false, true, eVolume::v100, true};
std::vector<std::vector<char> > Game::_savedMap;
bool Game::_KeyBind = false;
int	Game::_startLevel = 0;
