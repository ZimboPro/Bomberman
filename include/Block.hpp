#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "VisibleGameObject.hpp"

class Block: public VisibleGameObject
{
    public:

        Block();
        Block(Model_Texture & texture, float x, float y, bool isBreakable);
        ~Block();
};

#endif