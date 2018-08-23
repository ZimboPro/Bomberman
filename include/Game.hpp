//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game
{
public:
    static void start();

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
    static Player _player;
};

#endif //BOMBERMAN_GAME_HPP
