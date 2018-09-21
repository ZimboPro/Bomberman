#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

#include <vector>
#include <Model_Sprite.hpp>

class Shaders;
class Text;

class GameInterface
{
    public:
        GameInterface();
        ~GameInterface();

        void display();

        void load();
        void resetHOD();
        void resetTime(float seconds);
        void adjustLives(int i);
        void adjustScore(int score);
        bool stillAlive();
        bool timerEnded();
    
    private:
        Model_Sprite * _model;
        Shaders * _shader;
        Shaders * _textShader;
        Text * _text;

        std::vector<glm::vec2> _postions;

        float _endTime;
        static int _lives;
        static int _score;
        glm::mat4 _projection;
        glm::mat4 _view;
        glm::vec3 _color;
};

#endif