#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(ModelTexture & texture, float x, float y ): VisibleGameObject(texture, x, y, false, false)
{
}

Grass::~Grass()
{

}