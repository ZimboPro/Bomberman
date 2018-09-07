//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <Window.hpp>
#include "GameObjectManager.hpp"
#include "Camera.hpp"
#include <map>
#include "eKeys.hpp"

class Game
{
public:
    static void start();
    static int getKeyConfigured(eKeys key);
    static bool setKeyConfigured(eKeys key, int keycode);
    static Window _window;
    static eKeys keyPressed();

private:
    static bool isExiting();
    static void gameLoop();
//	static void showSplashScreen();
	static void showMenu();
	static void playGame();
    static void loadKeys();

    enum eGameState { Uninitialized, ShowingSplash, Paused,
            ShowingMenu, Playing, Exiting };

    static eGameState _gameState;
    static GameObjectManager _gameObjectManager;
    static int _keyPress;
    static Camera _camera;
    static std::map<eKeys, int> _keyConfiguration;
};

#endif //BOMBERMAN_GAME_HPP
