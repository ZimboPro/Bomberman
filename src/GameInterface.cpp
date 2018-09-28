#include <Shaders.hpp>
#include <Text.hpp>
#include "GameInterface.hpp"
#include "Game.hpp"


/*
    number of lives
    score
    timer
*/

Model_Sprite *          GameInterface::_model;
Model_Sprite *          GameInterface::_bomb;
Shaders *               GameInterface::_shader;
Shaders *               GameInterface::_textShader;
Text *                  GameInterface::_text;

std::vector<glm::vec2>  GameInterface::_postions;

float                   GameInterface::_endTime = 10;
int                     GameInterface::_lives = 3;
float                   GameInterface::_rangeMultiplier = 1;
int                     GameInterface::_bombMultiplier = 1;
int                     GameInterface::_score = 0;
int                     GameInterface::_troopaKilled = 0;
int                     GameInterface::_goombaKilled = 0;
int                     GameInterface::_totalEnemiesInPlay = 0;
bool                    GameInterface::_wonLevel = false;
glm::mat4               GameInterface::_projection;
glm::mat4               GameInterface::_view;
glm::vec3               GameInterface::_color;


void GameInterface::deleteObjects()
{
    delete _model;
    delete _shader;
    delete _textShader;
    delete _bomb;
}

void GameInterface::loadObjects()
{
    _model = new Model_Sprite("../../Assets/pickups/heart.obj");
    _bomb = new Model_Sprite("../../Assets/game_models/bomb_carry.obj");
    _text = new Text("../assets/shaders/OCRAEXT.TTF");

    _shader = new Shaders("../assets/shaders/vert/MeshVert.glsl","../assets/shaders/frag/MeshFrag.glsl");
    _textShader = new Shaders("../assets/shaders/vert/TextVert.glsl","../assets/shaders/frag/TextFrag.glsl");

    _color = glm::vec3(1, 1, 0);
}

void GameInterface::resetPostions()
{
    float y = Game::_window.Height() - Game::_window.Height() / 20;
    float x = Game::_window.Width() / 5;
    _projection = Game::_window.Projection();

    _postions.clear();
    _postions.push_back(glm::vec2(x * 1 - 60, y));
    _postions.push_back(glm::vec2(x * 2 - 60, y));
    _postions.push_back(glm::vec2(x * 3 - 80, y));
    _postions.push_back(glm::vec2(x * 4 + 30, y));
    _model->Reset();
    _model->Position(x - 90.0f, -20.0f, y);
    _model->Scale(3);
    _bomb->Reset();
    _bomb->Position(x * 4, -20.0f, y);
    _bomb->Scale(1);
}

void GameInterface::resetHOD()
{
    _lives = 3;
    _score = 0;
    _goombaKilled = 0;
    _troopaKilled = 0;
    _rangeMultiplier = 1;
}

void GameInterface::display()
{
    _shader->use();
    _shader->setMat4("projection", _projection);
	_shader->setMat4("view", _view);
    _model->Draw(*_shader);
    _bomb->Draw(*_shader);

    int timeLeft = _endTime - glfwGetTime();
    int min = timeLeft / 60;
    int sec = timeLeft % 60;
    

    std::string s = std::to_string(sec);
    if (s.length() == 1)
        s.insert(0, "0");
    
    _text->Render(*_textShader, "x" + std::to_string(_lives), _postions[0].x, _postions[0].y, 1, _color, Game::_window.Width(), Game::_window.Height());
    _text->Render(*_textShader,std::to_string(min) + ":" + s , _postions[1].x, _postions[1].y, 1, _color, Game::_window.Width(), Game::_window.Height());
    _text->Render(*_textShader, "Score:" + std::to_string(_score), _postions[2].x, _postions[2].y, 1, _color, Game::_window.Width(), Game::_window.Height());
    _text->Render(*_textShader, "x" + std::to_string(_bombMultiplier), _postions[3].x, _postions[3].y, 1, _color, Game::_window.Width(), Game::_window.Height());
}

int GameInterface::getRangeMultiplier()
{
    return _rangeMultiplier;
}

void GameInterface::increaseRangeMultiplier()
{
    _rangeMultiplier += 0.5;
    _bombMultiplier++;
}

void GameInterface::resetRangeMultiplier()
{
    _rangeMultiplier = 1;
    _bombMultiplier = 1;
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
    return (_lives > 0);
}

void GameInterface::resetTime(float seconds)
{
    _endTime = seconds + glfwGetTime();
}

bool GameInterface::timerEnded()
{
    return (_endTime < glfwGetTime());
}

void GameInterface::goombaKilled()
{
    _goombaKilled++;
    _totalEnemiesInPlay--;
}

void GameInterface::troopaKilled()
{
    _troopaKilled++;
    _totalEnemiesInPlay--;
}

bool GameInterface::allEnemiesDead()
{
    return(_totalEnemiesInPlay == 0);
}

void GameInterface::incrementTotalEnemies()
{
	_totalEnemiesInPlay++;
}

int GameInterface::amountOfGoombaKilled()
{
    return _goombaKilled;
}

int GameInterface::amountOfTroopaKilled()
{
    return _troopaKilled;
}

int GameInterface::LivesLeft()
{
    return _lives;
}

float GameInterface::TimeLeft()
{
    return (_endTime - glfwGetTime());
}

int GameInterface::CurrentScore()
{
    return _score;
}

bool GameInterface::completedLevel()
{
    return _wonLevel;
}

void GameInterface::setLevelCompleted(bool complete)
{
    _wonLevel = complete;
}

void GameInterface::setLives(int value)
{
    _lives = value;
}

void GameInterface::setNumEnemies(int value)
{
    _totalEnemiesInPlay = 5 - value;
}

void GameInterface::setScore(int value)
{
    _score = value;
}

void GameInterface::setTime(float value)
{
    _endTime = value;
}
