#ifndef GRASS_HPP
#define GRASS_HPP

#include "VisibleGameObject.hpp"

class Grass: public VisibleGameObject
{
    public:

        Grass();
        Grass(Model_Texture & texture, float x, float y, bool isBreakable);
        ~Grass();
};

#endif