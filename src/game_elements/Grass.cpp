#include "game_elements/Grass.hpp"

Grass::Grass()
{

}

Grass::Grass(Grass const & src)
{
	*this = src;
}

Grass::Grass(Model_Texture & texture, float x, float y ): VisibleGameObject(texture, x, y, false, false)
{
	VisibleGameObject::_model.Position(x, y, -32);
}

Grass::~Grass()
{
}