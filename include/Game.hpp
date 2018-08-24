//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "GameObjectManager.hpp"

class Game
{
public:
    static void start();
	static int getInput();
	static sf::Vector2u getWindowSize();

private:
    static bool isExiting();
    static void gameLoop();
	static void showSplashScreen();
	static void showMenu();
	static void playGame();

    enum eGameState { Uninitialized, ShowingSplash, Paused,
            ShowingMenu, Playing, Exiting };

    static eGameState _gameState;
    static sf::RenderWindow _window;
    static GameObjectManager _gameObjectManager;
    static int _keyPress;
};

#endif //BOMBERMAN_GAME_HPP
