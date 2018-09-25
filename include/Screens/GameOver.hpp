#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "ServiceLocator.hpp"

class Model_Sprite;
class Shaders;

class GameOver
{
    public:
        GameOver();
        ~GameOver();

        void show();
    private:
        Model_Sprite * _model;
        Shaders * _shader;
        IAudioProvider * _sound;
};

#endif
