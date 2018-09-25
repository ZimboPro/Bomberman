#ifndef GAMEWON_HPP
#define GAMEWON_HPP

#include "ServiceLocator.hpp"

class Model_Sprite;
class Shaders;

class GameWon
{
    public:
        GameWon();
        ~GameWon();

        void show();
    private:
        Model_Sprite * _model;
        Shaders * _shader;
        IAudioProvider * _sound;
};

#endif
