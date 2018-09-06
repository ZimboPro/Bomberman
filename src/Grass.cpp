#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(ModelTexture & texture, float x, float y, bool isBreakable)
{
    VisibleGameObject::VisibleGameObject(texture, x, y, true, false);
}

Grass::~Grass()
{

}