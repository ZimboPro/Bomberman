#include "Block.hpp"

Block::Block()
{

}

Block::Block(Model_Texture & texture, float x, float y, bool isBreakable): VisibleGameObject(texture, x, y, true, isBreakable)
{
}

Block::~Block()
{

}