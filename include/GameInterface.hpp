#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

#include <vector>
#include <Model_Sprite.hpp>

class Shaders;

class GameInterface
{
    public:
        GameInterface();
        ~GameInterface();

        void display(Shaders & shader);

        void load();
        void resetTime(float seconds);
        void adjustLives(int i);
        void adjustScore(int score);
        bool stillAlive();
    
    private:
        Model_Sprite * _models;
        std::vector<glm::vec3> _postions;
        float _endTime;
        int _lives;
        int _score;
};

#endif