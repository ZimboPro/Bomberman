#include <Shaders.hpp>
#include "GameInterface.hpp"
#include "Game.hpp"


/*
    number of lives
    score
    timer
*/
GameInterface::GameInterface()
{
    load();
}

GameInterface::~GameInterface()
{
        delete this->_models;
}

void GameInterface::load()
{
    // this->_models.push_back(new Model_Sprite("heart"));
    float y = Game::_window.Height() / 10;
    float x = Game::_window.Width() / 4;
    // for (size_t i = 0; i < )
}

void GameInterface::resetTime(float time)
{
    this->_endTime = glfwGetTime();
}

void GameInterface::display(Shaders & shader)
{
    shader.use();
}