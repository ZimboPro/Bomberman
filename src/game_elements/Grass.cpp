#include "game_elements/Grass.hpp"

Grass::Grass()
{
	_type = grass;
}

Grass::Grass(Grass const & src)
{
	*this = src;
	_type = grass;
}

Grass::Grass(Model_Texture & texture, float x, float y ): VisibleGameObject(texture, x, y, false, false)
{
	VisibleGameObject::_model.Position(x, y, -32);
}

Grass::~Grass()
{
}