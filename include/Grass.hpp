#ifndef GRASS_HPP
#define GRASS_HPP

#include "VisibleGameObject.hpp"

class Grass: public VisibleGameObject
{
    public:

        Grass();
        Grass(ModelTexture & texture, float x, float y);
        ~Grass();
};

#endif