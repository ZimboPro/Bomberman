//
// Created by Patrick RUSSELL on 2018/09/20.
//

#include <GameObjectManager.hpp>
#include "game_elements/Fire.hpp"

Fire::Fire(): _burnTime(5.0)
{
	_type = fire;
}

Fire::Fire(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_type = fire;
	_burnTime = 20;
}

Fire::~Fire()
{
}

BoundingBox Fire::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("fire object not loaded");

	float modelSize = 1;

	_box.x1 = _model.GetPosition().x;
	_box.x2 = _model.GetPosition().x + modelSize;
//	std::cout << " minX "<< _box.x1 << " maxX "<<_box.x2 << std::endl;
	_box.y1 = _model.GetPosition().z;
	_box.y2 = _model.GetPosition().z + modelSize;
//	std::cout << " minY "<< _box.y1 << " maxY "<<_box.y2 << std::endl;

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
