#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(Model *model, float x, float y)
{
    VisibleGameObject::VisibleGameObject(model, x, y, true, false);
}

Grass::~Grass()
{

}