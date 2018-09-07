#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(Model_Texture & texture, float x, float y, bool isBreakable)
{
    VisibleGameObject::VisibleGameObject(texture, x, y, true, false);
}

Grass::~Grass()
{

}