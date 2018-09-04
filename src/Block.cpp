#include "Block.hpp"

Block::Block()
{

}

Block::Block(Model *model, float x, float y, bool isBreakable)
{
    VisibleGameObject::VisibleGameObject(model, x, y, true, isBreakable);
}

Block::~Block()
{

}