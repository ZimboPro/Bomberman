//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <Error.hpp>
#include "Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "eKeys.hpp"

Player::Player(): _speed(0), _maxVelocity(600.0f)
{
	_type = player;
}

Player::Player(Model_Texture & texture, float x, float y): _speed(2.0f), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
}

Player::~Player() {}

BoundingBox Player::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Player object not loaded");

	_box.x1 = static_cast<float>(_model.GetPosition().x - 0.010);
	_box.x2 = _box.x1 + 0.1f;

	_box.y1 = static_cast<float>(_model.GetPosition().z - 0.010);
	_box.y2 = _box.y1 + 0.1f;

	return _box;
}

void Player::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();

	if (Game::keyPressed() == eKeys::Up)
	{
		if (_direction != 270) {
			_model.Rotate(270);
			_direction = 270;
		}
		if(GameObjectManager::collidesWith(*this, pos.x - displacement, pos.z) == grass)
			_model.Move(0 - displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		if (_direction != 90) {
			_model.Rotate(90);
			_direction = 90;
		}
		if(GameObjectManager::collidesWith(*this, pos.x + displacement, pos.z) == grass)
		_model.Move(0 + displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		if (_direction != 0) {
			_model.Rotate(0);
			_direction = 0;
		}
		if(GameObjectManager::collidesWith(*this, pos.x,  pos.z + displacement) == grass)
		_model.Move(0 , 0 + displacement);
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		if (_direction != 180) {
			_model.Rotate(180);
			_direction = 180;
		}
		if(GameObjectManager::collidesWith(*this, pos.x, pos.z - displacement) == grass)
		_model.Move(0 , 0 - displacement);
	}
}