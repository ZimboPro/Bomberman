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
#include "Map.hpp"
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

	_gameState = eGameState::ShowingMenu;

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);

	loadKeys();
	while (!isExiting())
	{
		gameLoop();
	}
	_interface.deleteObjects();
	ServiceLocator::getAudio()->stopAllSounds();
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
			exit(0);
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
	GameObjectManager::killItWithFire();
	LevelPassed levelPassed;
	_loadedLevel = false;
	_wonLevel = true;
	levelPassed.show();
	_startLevel += 1;
	_gameState = Playing;
}

void Game::lostLevel()
{
	GameOver gameover;

	GameObjectManager::killItWithFire();
	_loadedLevel = false;
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
		_gameState = Exiting;
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
	IAudioProvider * sound = ServiceLocator::getAudio();
	sound->setSoundLevel(_settings.volume * 20);
	sound->stopAllSounds();
	if (_settings.music)
		sound->playSong("../../Assets/sounds/background_music/credits.wav", true);
	splash.show(shader, "../../Assets/intro/", 238);

	_gameState = Game::ShowingMenu;
}

void Game::showLevelSelect()
{
	LevelSelectMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
	switch(selection)
	{
		case LevelSelectMenu::Infinite:
			Game::_startLevel = 0;
			_gameState = Playing;
			break;
		case LevelSelectMenu::Classic:
			Game::_startLevel = 1;
			_gameState = Playing;
			break;
		case LevelSelectMenu::Back:
			_gameState = ShowingStartGameMenu;		
			break;
	}
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

	if (!_wonLevel)
		_interface.resetHOD();
	else
		_wonLevel = false;
	_interface.resetTime(300);
	_interface.resetPostions();

	if (_loadedLevel)
	{
		try
		{
			GameObjectManager::loadLevel(Map::_levels.load());
		}
		catch(std::exception &e)
		{
			_loadedLevel = !_loadedLevel;
			std::cout << std::endl << e.what() << std::endl;
			_gameState = ShowingStartGameMenu;
		}
	}
	_interface.setLevelCompleted(false);
	sf::Clock clock;

	Shaders shader("_deps/graphics-src/Resources/VertexShaders/ShadedModelsVert.glsl",
			"_deps/graphics-src/Resources/FragmentShaders/ShadedModelsFrag.glsl");

	_camera.LookAt(glm::vec3(0));

	IAudioProvider * sound = ServiceLocator::getAudio();
	sound->setSoundLevel(_settings.volume * 20);

	sound->stopAllSounds();
	if (_settings.music)
		sound->playSong("../../Assets/sounds/background_music/gameplay_background_track.wav", true);
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

		if(_window.isKeyPressed(getKeyConfigured(eKeys::Escape)))
		{
			float timeLeft = GameInterface::TimeLeft();
			if (_settings.sound)
				sound->playSound("../../Assets/sounds/gameplay/pause_game.wav");
			showPauseMenu();
			GameInterface::resetTime(timeLeft);
			sound->stopAllSounds();
			clock.restart();
			if (_settings.music && !sound->isSongPlaying())
				sound->playSong("../../Assets/sounds/background_music/gameplay_background_track.wav", true);
		}
		if (_interface.timerEnded() || !_interface.stillAlive())
			_gameState = Game::LostLevel;

		if (_interface.completedLevel())
			_gameState = Game::WonLevel;

		if (_window.closed())
		{
			// GameObjectManager::killItWithFire();
			_gameState = Exiting;
		}
	}
	return ;
}

void Game::showCredits()
{
	Shaders shader("../assets/shaders/vert/SpriteVert.glsl", "../assets/shaders/frag/SpriteFrag.glsl");

	SplashScreen splash;
	IAudioProvider * sound = ServiceLocator::getAudio();
	sound->setSoundLevel(_settings.volume * 20);
	sound->stopAllSounds();
	if (_settings.music)
		sound->playSong("../../Assets/sounds/background_music/credits.wav", true);
	splash.show(shader, "../../Assets/credits/", 222);
	_gameState = Game::ShowingMenu;
}

void Game::save()
{
	int width = Map::width();
	int	height = Map::height();
	int lives = GameInterface::LivesLeft();
	int	score = GameInterface::CurrentScore();
	int	enemiesKilled = GameInterface::amountOfGoombaKilled() + GameInterface::amountOfTroopaKilled();
	int	timeLeft = GameInterface::TimeLeft();

	std::vector<std::vector<char> > saveMap(height, std::vector<char>(width, '0'));
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (Map::at(x, y) == '1' || Map::at(x, y) == '2' || Map::at(x, y) == 'G')
			{
				saveMap[y][x] = '1';
			}
		}
	}
	Map::_levels.save(saveMap, enemiesKilled, lives, score, timeLeft);
}

void Game::load()
{
	std::cout << "Loading\n";
	_loadedLevel = true;
	_gameState = Playing;
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

void	Game::setGameStateGameWon()
{
	_gameState = ShowingMenu;
}

Game::eGameState Game::_gameState = Game::Uninitialized;
Window Game::_window("Bomberman", 1024, 768);
Camera Game::_camera(glm::vec3(15.0f, 25.0f, 0.0f));
std::map<eKeys, int> Game::_keyConfiguration;
LoadingScreen Game::_loadingScreen;
Settings Game::_settings{eScreen::s1024, false, false, eVolume::v100, false};
bool Game::_KeyBind = false;
bool Game::_loadedLevel = false;
bool Game::_wonLevel = false;
int	Game::_startLevel = 0;
