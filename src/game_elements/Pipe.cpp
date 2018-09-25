//
// Created by Patrick Russell on 2018/09/25.
//

#include "game_elements/Pipe.hpp"


Pipe::Pipe()
{
	_type = gate;
}

Pipe::Pipe(Pipe const & src)
{
	*this = src;
}

Pipe::Pipe(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_type = gate;
}

Pipe::~Pipe() {}

BoundingBox Pipe::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("powerBlock object not loaded");

	float modelSize = 0.6f;
	glm::vec3 pos = _model.GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

