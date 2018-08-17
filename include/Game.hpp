//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
    static void start();

private:
    static bool isExiting();
    static void gameLoop();

    enum eGameState { Uninitialized, ShowingSplash, Paused,
            ShowingMenu, Playing, Exiting };

    static eGameState _gameState;
    static sf::RenderWindow _window;
};

#endif //BOMBERMAN_GAME_HPP
