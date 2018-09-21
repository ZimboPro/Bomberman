#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

#include <vector>
#include <Model_Sprite.hpp>

class Shaders;
class Text;

class GameInterface
{
    public:
        static void loadObjects();
        static void deleteObjects();
        
        static void display();
        
        static void resetHOD();
        static void resetTime(float seconds);
        static void resetPostions();
        
        static void adjustLives(int i);
        static void adjustScore(int score);
    
        static bool stillAlive();
        static bool timerEnded();

        static void goombaKilled();
        static void troopaKilled();
        static int amountOfGoombaKilled();
        static int amountOfTroopaKilled();

        static int LivesLeft();
        static float TimeLeft();
        static int CurrentScore();
    
    private:
        static Model_Sprite * _model;
        static Shaders * _shader;
        static Shaders * _textShader;
        static Text * _text;

        static std::vector<glm::vec2> _postions;

        static float _endTime;
        static int _lives;
        static int _score;
        static int _goombaKilled;
        static int _troopaKilled;
        static glm::mat4 _projection;
        static glm::mat4 _view;
        static glm::vec3 _color;
};

#endif