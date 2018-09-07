#include "Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(Model_Texture & texture, float x, float y ): VisibleGameObject(texture, x, y, false, false)
{
}

Grass::~Grass()
{

}