//
// Created by Patrick RUSSELL on 2018/09/13.
//

#include <GameObjectManager.hpp>
#include "game_elements/Bomb.hpp"

Bomb::Bomb(): _timeTillExplode(5.0)
{
	_type = bomb;
}

Bomb::Bomb(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_type = bomb;
	_timeTillExplode = 2;
}

Bomb::~Bomb()
{
}

BoundingBox Bomb::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Bomb object not loaded");

	float modelSize = 0.6f;

	_box.x1 = _model.GetPosition().x;
	_box.x2 = _model.GetPosition().x + modelSize;

	_box.y1 = _model.GetPosition().z;
	_box.y2 = _model.GetPosition().z + modelSize;

	return _box;
}

void Bomb::Update(float & timeElapsed)
{
	if (_timeTillExplode > 0)
		_timeTillExplode -= timeElapsed;
	else
	{
		GameObjectManager::explodeBomb(this);
	}
}
