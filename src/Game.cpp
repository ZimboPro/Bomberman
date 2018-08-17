//
// Created by Patrick RUSSELL on 2018/08/17.
//

#include "Game.hpp"

void Game::start()
{
    if (_gameState != Uninitialized)
        return;

    _window.create(sf::VideoMode(800, 600), "Test");
    _gameState = Game::Playing;

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
    sf::Event event;

    while(_window.pollEvent(event))
    {
        switch(_gameState)
        {
        	case Game::Playing:
        		_window.clear(sf::Color::Magenta);
        		_window.display();
        		if (event.type == sf::Event::Closed || event.type == sf::Keyboard::Escape)
        			_gameState = Game::Exiting;
        		break;

        }
    }
}

Game::eGameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_window;

