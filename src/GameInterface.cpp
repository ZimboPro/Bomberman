#include <Shaders.hpp>
#include <Text.hpp>
#include "GameInterface.hpp"
#include "Game.hpp"


/*
    number of lives
    score
    timer
*/

int GameInterface::_lives;
int GameInterface::_score;

GameInterface::GameInterface()
{
    load();
}

GameInterface::~GameInterface()
{
    delete this->_model;
    delete this->_shader;
    delete this->_textShader;
}

void GameInterface::load()
{
    this->_model = new Model_Sprite("../../Assets/pickups/heart.obj");
    this->_text = new Text("../assets/shaders/OCRAEXT.TTF");

    this->_shader = new Shaders("../assets/shaders/vert/MeshVert.glsl","../assets/shaders/frag/MeshFrag.glsl");
    this->_textShader = new Shaders("../assets/shaders/vert/TextVert.glsl","../assets/shaders/frag/TextFrag.glsl");

    float y = Game::_window.Height() / 20;
    float x = Game::_window.Width() / 4;

    this->_postions.push_back(glm::vec2(x * 1 - 40, y));
    this->_postions.push_back(glm::vec2(x * 2 - 40, y));
    this->_postions.push_back(glm::vec2(x * 3 - 40, y));
    this->_model->Position(x - 70.0f, -20.0f, y);
    this->_model->Scale(3);

    this->_projection = Game::_window.Projection();
    this->_color = glm::vec3(1, 1, 0);
}

void GameInterface::resetHOD()
{
    _lives = 3;
    _score = 0;
}

void GameInterface::display()
{
    this->_shader->use();
    this->_shader->setMat4("projection", this->_projection);
	this->_shader->setMat4("view", this->_view);
    this->_model->Draw(*this->_shader);

    int timeLeft = this->_endTime - glfwGetTime();
    int min = timeLeft / 60;
    int sec = timeLeft % 60;

    std::string s = std::to_string(sec);
    if (s.length() == 1)
        s.insert(0, "0");
    
    this->_text->Render(*this->_textShader, "x" + std::to_string(_lives), this->_postions[0].x, this->_postions[0].y, 1, this->_color, Game::_window.Width(), Game::_window.Height());
    this->_text->Render(*this->_textShader,std::to_string(min) + ":" + s , this->_postions[1].x, this->_postions[1].y, 1, this->_color, Game::_window.Width(), Game::_window.Height());
    this->_text->Render(*this->_textShader, "Score:" + std::to_string(_score), this->_postions[2].x, this->_postions[2].y, 1, this->_color, Game::_window.Width(), Game::_window.Height());
}

void GameInterface::adjustLives(int lives)
{
    _lives += lives;
}

void GameInterface::adjustScore(int score)
{
    _score += score;
}

bool GameInterface::stillAlive()
{
    return (_lives > -1);
}

void GameInterface::resetTime(float seconds)
{
    this->_endTime = seconds + glfwGetTime();
}

bool GameInterface::timerEnded()
{
    return (this->_endTime < glfwGetTime());
}