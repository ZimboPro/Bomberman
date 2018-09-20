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

void Fire::Update(float & timeElapsed)
{
	if (_burnTime > 0)
		_burnTime -= timeElapsed;
	else
	{
		GameObjectManager::removeDynamicObject(this);
	}
}
