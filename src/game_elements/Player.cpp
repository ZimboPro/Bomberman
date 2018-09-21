//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <cstdlib>
#include <Error.hpp>
#include "game_elements/Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "eKeys.hpp"
#include <ctime>
#include <unistd.h>

Player::Player(): _speed(0), _maxVelocity(600.0f)
{
	_index = 0;
	_prevIndex = 0;
	_totalElapsed = 0.0f;
	_type = player;
	
}

Player::Player(Player const & src)
{
	_totalElapsed = 0.0f;
	_index = 0;
	_prevIndex = 0;
	*this = src;
}

Player::Player(Model_Texture & texture, float x, float y): _speed(3.0f), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
	_totalElapsed = 0.0f;
	_prevIndex = 0;
	_index = 0;
}

Player::Player(std::vector<Model_Texture *> & textures, float x, float y): _speed(3.0f), _maxVelocity(600.0f)
{
	VisibleGameObject::_isBreakable = false;
	VisibleGameObject::_isLoaded = true;
	VisibleGameObject::_isCollidable = true;
	_prevIndex = 0;
	_totalElapsed = 0.0f;
	_index = 0;
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[1]));
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[2]));

	for (size_t i = 0; i < this->_models.size(); i++)
	{
		this->_models[i]->Position(x, y);
		this->_models[i]->Scale(0.032f);
	}
	_direction = 0;
}

Player::~Player()
{
	for (size_t i = 0; i < this->_models.size(); i++)
		delete this->_models[i];
}

BoundingBox Player::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Player object not loaded");

	float modelSize = 0.6f;
	glm::vec3 pos = _models[0]->GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

void Player::dropBomb()
{
	glm::vec3 pos = _models[0]->GetPosition();
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

void Player::Draw(Shaders & shader)
{
	if(_models[_index]->IsLoaded())
		_models[_index]->Draw(shader);
}

void Player::Update(float & timeElapsed)
{
	float camDisplacement = timeElapsed * _speed;
	BoundingBox box = this->getBoundingBox();
	_prevIndex = _index;
	float displacement = _totalElapsed * _speed;
	glm::vec3 pos = _models[0]->GetPosition();

	if (Game::keyPressed() == eKeys::Up)
	{
		if (_direction != 270) {
			Rotate(270);
			_direction = 270;
		}
		setDirection(270);
		box.x1 -= displacement;
		box.x2 -= displacement;
		if(GameObjectManager::collidesWith(box, _type) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0 - camDisplacement, 0);
			if (_totalElapsed > 0.2f)
				Move(0 - displacement, 0);
		}
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		if (_direction != 90) {
			Rotate(90);
			_direction = 90;
		}
		box.x1 += displacement + 0.2;
		box.x2 += displacement + 0.2;
		if(GameObjectManager::collidesWith(box, _type) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0 + camDisplacement, 0);
			if (_totalElapsed > 0.2f)
				Move(0 + displacement, 0);
		}
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		if (_direction != 0) {
			Rotate(0);
			_direction = 0;
		}
		box.y1 += displacement + 0.2;
		box.y2 += displacement + 0.2;
		if(GameObjectManager::collidesWith(box, _type) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0, 0 + camDisplacement);
			if (_totalElapsed > 0.2f)
				Move(0 , 0 + displacement);
		}
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		if (_direction != 180) {
			Rotate(180);
			_direction = 180;
		}
		box.y1 -= displacement;
		box.y2 -= displacement;
		if(GameObjectManager::collidesWith(box, _type) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0, 0 - camDisplacement);
			if (_totalElapsed > 0.2f)
				Move(0 , 0 - displacement);
		}
	}
	else if (Game::keyTyped() == eKeys::Select)
		dropBomb();
	else if (Game::keyTyped() == eKeys::Undefined)
	{
		if (_direction == 0)
			Move(0 , 0 - displacement);
		else if (_direction == 90)
			Move(0 + displacement, 0);
		else if (_direction == 180)
			Move(0 , 0 - displacement);
		else if (_direction == 270)
			Move(0 - displacement, 0);
		_index = 0;
	}	
}

void Player::Move(float x, float y)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Move(x, y);
	if (_prevIndex == _index)
		_index = (_index + 1) % this->_models.size();
	_totalElapsed = 0.0f;
}

void Player::Rotate(float degrees)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Rotate(degrees);
	if (_prevIndex == _index)
		_index = (_index + 1) % this->_models.size();
	_totalElapsed = 0.0f;
}