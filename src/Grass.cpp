#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(Model *model, float x, float y, bool isBreakable)
{
    VisibleGameObject::VisibleGameObject(model, x, y, true, false);
}

Grass::~Grass()
{

}