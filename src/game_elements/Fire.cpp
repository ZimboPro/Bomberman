//
// Created by Patrick RUSSELL on 2018/09/20.
//

#include <GameObjectManager.hpp>
#include "game_elements/Fire.hpp"
#include "Game.hpp"

Fire::Fire(): _burnTime(2.0)
{
	_type = fire;
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
}

Fire::Fire(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_type = fire;
	_burnTime = 2.0;
	_model.Move(0, 0, -0.5);
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/gameplay/fire.wav");
}

Fire::~Fire()
{}

BoundingBox Fire::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("fire object not loaded");

	float modelSize = 0.5;

	_box.x1 = _model.GetPosition().x - modelSize;
	_box.x2 = _model.GetPosition().x + modelSize;
	_box.y1 = _model.GetPosition().z - modelSize;
	_box.y2 = _model.GetPosition().z + modelSize;

	return _box;
}

void Fire::Update(float & timeElapsed)
{
	float rotationMultiplier = 1000;
	if (_burnTime > 0)
	{
		_burnTime -= timeElapsed;
		glm::vec3 pos = _model.GetPosition();
		if (pos.y < 0)
		{
			_model.Move(0, 0, timeElapsed * _speed, rotationMultiplier * timeElapsed * _speed);
		}
		else
		{
			_model.Move(0, 0, -timeElapsed * _speed, rotationMultiplier * timeElapsed * _speed);
		}
		BoundingBox box = getBoundingBox();
		GameObjectManager::collidesWithPlayer();
	}
	else
	{
		GameObjectManager::removeDynamicObject(this);
	}
}
