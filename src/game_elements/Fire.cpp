//
// Created by Patrick RUSSELL on 2018/09/20.
//

#include <GameObjectManager.hpp>
#include "game_elements/Fire.hpp"

Fire::Fire(): _burnTime(5.0)
{
	_type = bomb;
}

Fire::Fire(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_burnTime = 2;
}

Fire::~Fire()
{
}

BoundingBox Fire::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("fire object not loaded");

	float modelSize = 0.6f;

	_box.x1 = _model.GetPosition().x;
	_box.x2 = _model.GetPosition().x + modelSize;

	_box.y1 = _model.GetPosition().z;
	_box.y2 = _model.GetPosition().z + modelSize;

	return _box;
}

void Fire::Update(float & timeElapsed)
{
	if (_burnTime > 0)
		_burnTime -= timeElapsed;
	else
	{
		GameObjectManager::removeDynamicObject(this);
	}
}
