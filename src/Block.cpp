#include "Block.hpp"

Block::Block()
{

}

Block::Block(ModelTexture & texture, float x, float y, bool isBreakable)
{
    VisibleGameObject::VisibleGameObject(texture, x, y, true, isBreakable);
}

Block::~Block()
{

}