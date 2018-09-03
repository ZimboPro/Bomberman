//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <Window.hpp>
#include "GameObjectManager.hpp"
#include "Camera.hpp"

class Game
{
public:
    static void start();
	static int getInput();

private:
    static bool isExiting();
    static void gameLoop();
//	static void showSplashScreen();
//	static void showMenu();
	static void playGame();

    enum eGameState { Uninitialized, ShowingSplash, Paused,
            ShowingMenu, Playing, Exiting };

    static eGameState _gameState;
    static Window _window;
    static GameObjectManager _gameObjectManager;
    static int _keyPress;
    static Camera _camera;
};

#endif //BOMBERMAN_GAME_HPP
