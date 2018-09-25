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

Player::Player(): _speed(3.0f)
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
	_totalDroppedWhilstDying = 0;
	*this = src;
}

Player::Player(Model_Texture & texture, float x, float y): _speed(3.0f), VisibleGameObject(texture, x, y, true, false)
{
	_totalElapsed = 0.0f;
	_prevIndex = 0;
	_index = 0;
	_type = player;
	_totalDroppedWhilstDying = 0;
}

Player::Player(std::vector<Model_Texture *> & textures, float x, float y): _speed(3.0f)
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
	_type = player;
	_totalDroppedWhilstDying = 0;
	_timeSpentDying = 0;
	_isDying = false;
	_timeTodie = 3;

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
	float bombOffset = 0.5;
	float bombX = pos.x;
	float bombY = pos.z;

	if (_direction == 270) // UP
	{
		bombX = floor(bombX - bombOffset);
		bombY = round(bombY);
	}
	else if (_direction == 90) // Down
	{
		bombX = ceil(bombX + bombOffset);
		bombY = round(bombY);
	}
	else if (_direction == 0) // Left
	{
		bombY = ceil(bombY + bombOffset);
		bombX = round(bombX);
	}
	else if (_direction == 180) // Right
	{
		bombY = floor(bombY - bombOffset);
		bombX = round(bombX);
	}
	GameObjectManager::addDynamicObject(bomb, bombX ,bombY);
}

void Player::Draw(Shaders & shader)
{
	if(_models[_index]->IsLoaded())
		_models[_index]->Draw(shader);
}

void Player::dying(float & elapsedTime)
{
	float rotationMultiplier = 150;
	if(_timeSpentDying < _timeTodie)
	{
		_timeSpentDying += elapsedTime;
		Move(0, 0, (-elapsedTime * _speed) / _timeTodie);
		_totalDroppedWhilstDying += (elapsedTime * _speed) / _timeTodie;
		Rotate(_timeSpentDying * _speed * rotationMultiplier);
	}
	else
	{
		glm::vec3 pos = _models[0]->GetPosition();
		GameInterface::adjustLives(-1);
		GameInterface::resetRangeMultiplier();
		Move(-(pos.x - Map::getPlayerStartX()), -(pos.z - Map::getPlayerStartY()), _totalDroppedWhilstDying);
		Rotate(0);
		Game::_camera.Move(-(pos.x - Map::getPlayerStartX()), -(pos.z - Map::getPlayerStartY()));
		_totalDroppedWhilstDying = 0;
		_isDying = false;
		_timeSpentDying = 0;
	}
}

void Player::Update(float & timeElapsed)
{
	if(_isDying)
		dying(timeElapsed);

	float camDisplacement = timeElapsed * _speed;
	BoundingBox box = this->getBoundingBox();
	_prevIndex = _index;
	float displacement = _totalElapsed * _speed;
	float modelChangeTime = 0.13f;
	glm::vec3 pos = _models[0]->GetPosition();

	float alignX = round(pos.x) - pos.x;
	float alignY = round(pos.z) - pos.z;

	objectTypes collidesWith = GameObjectManager::collidesWith(box, _type);

	if (Game::keyPressed() == eKeys::Up)
	{
		Rotate(270);
		box.x1 -= displacement;
		box.x2 -= displacement;
		box.y1 += alignY;
		box.y2 += alignY;
		if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0 - camDisplacement, 0);
			if (_totalElapsed > modelChangeTime)
				Move(0 - displacement, alignY);
		}
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		Rotate(90);
		box.x1 += displacement + 0.2;
		box.x2 += displacement + 0.2;
		box.y1 += alignY;
		box.y2 += alignY;
		if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0 + camDisplacement, 0);
			if (_totalElapsed > modelChangeTime)
				Move(0 + displacement, alignY);
		}
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		Rotate(0);
		box.x1 += alignX;
		box.x2 += alignX;
		box.y1 += displacement + 0.2;
		box.y2 += displacement + 0.2;
		if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
		{
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0, 0 + camDisplacement);
			if (_totalElapsed > modelChangeTime)
				Move(alignX, 0 + displacement);
		}
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		Rotate(180);
		box.x1 += alignX;
		box.x2 += alignX;
		box.y1 -= displacement;
		box.y2 -= displacement;
		if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
		{
			_model.Move(0, 0 - displacement);
			_totalElapsed += timeElapsed;
			Game::_camera.Move(0, 0 - camDisplacement);
			if (_totalElapsed > modelChangeTime)
				Move(alignX, 0 - displacement);
		}
	}
	switch (collidesWith)
	{
		case fire:
			_isDying = true;
			break;
		case powerBlock:
			GameInterface::increaseRangeMultiplier();
			GameInterface::adjustScore(20);
			break;
		case healthBlock:
			GameInterface::adjustLives(1);
		case gate:
			//implement level change here
			break;
		default:
			break;
	}

	if (Game::keyTyped() == eKeys::Place && !_isDying)
		dropBomb();
}

void Player::Move(float x, float y, float z)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Move(x, y, z);
	if (_prevIndex == _index)
		_index = (_index + 1) % this->_models.size();
	_totalElapsed = 0.0f;
}

void Player::Rotate(float degrees)
{
	if (_direction != degrees)
	{
		_direction = degrees;
		for (size_t i = 0; i < this->_models.size(); i++)
			this->_models[i]->Rotate(degrees);
		if (_prevIndex == _index)
			_index = (_index + 1) % this->_models.size();
		_totalElapsed = 0.0f;
	}
}
