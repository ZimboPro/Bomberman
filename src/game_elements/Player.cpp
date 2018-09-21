//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <Error.hpp>
#include "game_elements/Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "eKeys.hpp"

Player::Player(): _speed(0), _maxVelocity(600.0f)
{
	_type = player;
}

Player::Player(Player const & src)
{
	*this = src;
}

Player::Player(Model_Texture & texture, float x, float y): _speed(3.0f), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
}

Player::~Player() {}

BoundingBox Player::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Player object not loaded");

	float modelSize = 0.6f;

	_box.x1 = _model.GetPosition().x;
	_box.x2 = _model.GetPosition().x + modelSize;

	_box.y1 = _model.GetPosition().z;
	_box.y2 = _model.GetPosition().z + modelSize;

	return _box;
}

void Player::dropBomb()
{
	glm::vec3 pos = _model.GetPosition();
	float playerOffset = 0.3;

	if (_direction == 270)
	{
		GameObjectManager::addDynamicObject(bomb, pos.x - 0.6, pos.z);
		_model.Move(playerOffset, 0);
	}
	else if (_direction == 90)
	{
		GameObjectManager::addDynamicObject(bomb, pos.x + 0.6, pos.z);
		_model.Move(-playerOffset, 0);
	}
	else if (_direction == 0)
	{
		GameObjectManager::addDynamicObject(bomb, pos.x, pos.z + 0.6);
		_model.Move(0, -playerOffset);
	}
	else if (_direction == 180)
	{
		GameObjectManager::addDynamicObject(bomb, pos.x, pos.z - 0.6);
		_model.Move(0, playerOffset);
	}
}

void Player::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();
	BoundingBox box = this->getBoundingBox();

	if (Game::keyPressed() == eKeys::Up)
	{
		setDirection(270);
		box.x1 -= displacement;
		box.x2 -= displacement;
		if(GameObjectManager::collidesWith(box, _type) == grass)
			_model.Move(0 - displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		setDirection(90);
		box.x1 += displacement + 0.2;
		box.x2 += displacement + 0.2;
		if(GameObjectManager::collidesWith(box, _type) == grass)
			_model.Move(0 + displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		setDirection(0);
		box.y1 += displacement + 0.2;
		box.y2 += displacement + 0.2;
		if(GameObjectManager::collidesWith(box, _type) == grass)
			_model.Move(0 , 0 + displacement);
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		setDirection(180);
		box.y1 -= displacement;
		box.y2 -= displacement;
		if(GameObjectManager::collidesWith(box, _type) == grass)
		{
			_model.Move(0, 0 - displacement);
		}
	}
	else if (Game::keyTyped() == eKeys::Select)
		dropBomb();
	Game::_camera.LookAt(_model.GetPosition());
}