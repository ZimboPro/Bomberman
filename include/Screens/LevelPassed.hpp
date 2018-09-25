#ifndef LEVELPASSED_HPP
#define LEVELPASSED_HPP

#include "ServiceLocator.hpp"

class Model_Sprite;
class Shaders;

class LevelPassed
{
    public:
        LevelPassed();
        ~LevelPassed();

        void show();
    private:
        Model_Sprite * _model;
        Shaders * _shader;
        IAudioProvider * _sound;
};

#endif
