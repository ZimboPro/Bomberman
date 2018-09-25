//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/HealthBlock.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"

HealthBlock::HealthBlock(): _speed(2)
{
	_type = healthBlock;
}

HealthBlock::HealthBlock(HealthBlock const & src)
{
	*this = src;
}

HealthBlock::HealthBlock(Model_Texture & texture, float x, float y): _speed(2), VisibleGameObject(texture, x, y, true, false)
{
	_type = healthBlock;
}

HealthBlock::~HealthBlock() {}

BoundingBox HealthBlock::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("healthBlock object not loaded");

	float modelSize = 0.3f;
	glm::vec3 pos = _model.GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

void HealthBlock::Update(float & timeElapsed)
{
	float rotationMultiplier = 100;
	_direction += timeElapsed * _speed;
	_model.Rotate(timeElapsed * _speed * rotationMultiplier);
}
