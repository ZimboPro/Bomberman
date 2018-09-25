//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/powerBlock.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

PowerBlock::PowerBlock(): _speed(2)
{
	_type = powerBlock;
}

PowerBlock::PowerBlock(PowerBlock const & src)
{
	*this = src;
}

PowerBlock::PowerBlock(Model_Texture & texture, float x, float y): _speed(2), VisibleGameObject(texture, x, y, true, false)
{
	_type = powerBlock;
}

PowerBlock::~PowerBlock() {}

BoundingBox PowerBlock::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("powerBlock object not loaded");

	float modelSize = 0.3f;
	glm::vec3 pos = _model.GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

void PowerBlock::Update(float & timeElapsed)
{
	float rotationMultiplier = 100;
	_direction += timeElapsed * _speed;
	_model.Rotate(timeElapsed * _speed * rotationMultiplier);
}
