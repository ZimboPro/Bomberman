//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/Goomba.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "Error.hpp"
#include "Map.hpp"

Goomba::Goomba(): _speed(3)
{
	init();
}

Goomba::Goomba(Model_Texture & texture, float x, float y): _speed(3), VisibleGameObject(texture, x, y, true, false)
{
	init();
}

Goomba::Goomba(Goomba const & src)
{
	*this = src;
	init();
}

Goomba::Goomba(std::vector<Model_Texture *> & textures, float x, float y) : _speed(3)
{
	init();
	VisibleGameObject::_timeTodie = 2;
	VisibleGameObject::_isBreakable = false;
	VisibleGameObject::_isLoaded = true;
	VisibleGameObject::_isCollidable = true;
	VisibleGameObject::_isDying = false;
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[1]));
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[2]));
	_timeSpentDying = 0;

	for (size_t i = 0; i < this->_models.size(); i++)
	{
		this->_models[i]->Position(x, y);
		this->_models[i]->Scale(0.032f);
	}
}

Goomba::~Goomba()
{
	for (size_t i = 0; i < this->_models.size(); i++)
		delete this->_models[i];
}

void Goomba::init()
{
	_type = goomba;
	_time = glfwGetTime();
	_index = 0;
	_direction = 0;
	_totalElapsed = 0.0f;
}

BoundingBox Goomba::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Goomba object not loaded");

	float modelSize = 0.6f;

	_box.x1 = static_cast<float>(this->_models[_index]->GetPosition().x);
	_box.x2 = static_cast<float>(this->_models[_index]->GetPosition().x + modelSize);

	_box.y1 = static_cast<float>(this->_models[_index]->GetPosition().z);
	_box.y2 = static_cast<float>(this->_models[_index]->GetPosition().z + modelSize);

	return _box;
}

void ShiftBox(BoundingBox & box, float x, float y)
{
	box.x1 += x;
	box.x2 += x;
	box.y1 += y;
	box.y2 += y;
}

void Goomba::RandomDirection()
{
	if (glfwGetTime() - _time > 1)
	{
		BoundingBox boxLeft = this->getBoundingBox();
		BoundingBox boxRight = this->getBoundingBox();
		BoundingBox boxUp = this->getBoundingBox();
		BoundingBox boxDown = this->getBoundingBox();
		ShiftBox(boxLeft, - ( 2 * 0.6f), 0.0f);
		ShiftBox(boxRight,( 2 * 0.6f), 0.0f);
		ShiftBox(boxUp, 0.0f, - ( 2 * 0.6f));
		ShiftBox(boxDown, 0.0f, ( 2 * 0.6f));

		std::vector<int> dir;
		//left
		if (GameObjectManager::collidesWith(boxLeft, _type) != unbreakableBlocks && GameObjectManager::collidesWith(boxLeft, _type) != breakableBlocks)
			dir.push_back(3);
		//right
		if (GameObjectManager::collidesWith(boxRight, _type) != unbreakableBlocks && GameObjectManager::collidesWith(boxRight, _type) != breakableBlocks)
			dir.push_back(4);
		//up
		if (GameObjectManager::collidesWith(boxUp, _type) != unbreakableBlocks && GameObjectManager::collidesWith(boxUp, _type) != breakableBlocks)
			dir.push_back(1);
		//down
		if (GameObjectManager::collidesWith(boxDown, _type) != unbreakableBlocks && GameObjectManager::collidesWith(boxDown, _type) != breakableBlocks)
			dir.push_back(2);
		if (dir.size() > 2)
		{
			int index = rand() % (100 * dir.size());
			_directionGen = dir[index / 100];
			// std::cout << dir.size() << " " << x << " " << y << std::endl;
			_time = glfwGetTime();
		}
	}
	// if (dir.size() > 2)
	// std::cout << dir.size() << " " << x << " " << y << std::endl;
	// }
}

void Goomba::dying(float & elapsedTime)
{
	if(_timeSpentDying < _timeTodie)
	{
		_timeSpentDying += elapsedTime;
		Move(0, 0, (-elapsedTime * _speed) / _timeTodie);
	}
	else
	{
		GameInterface::goombaKilled();
		GameInterface::adjustScore(20);
		_isLoaded = false;
		GameObjectManager::removeDynamicObject(this);
	}
}

void Goomba::Draw(Shaders & shader)
{
	if(_models[_index]->IsLoaded())
		_models[_index]->Draw(shader);
}

void Goomba::Update(float & timeElapsed)
{
	if (VisibleGameObject::_isDying)
	{
		dying(timeElapsed);
		return;
	}

	BoundingBox box = getBoundingBox();
	_totalElapsed += timeElapsed;

	if (_totalElapsed > 0.13f)
	{
		float displacement = _totalElapsed * _speed;
		RandomDirection();
		if (_directionGen == 1)
			movement(270, -displacement, 0, -displacement, 0, box);
		else if (_directionGen == 2)
			movement(90, displacement, 0, displacement + 0.2, 0, box);
		else if (_directionGen == 3)
			movement(0, 0, displacement, 0, displacement + 0.2, box);
		else if (_directionGen == 4)
			movement(180, 0, -displacement, 0, -displacement, box);
		_index = (_index + 1) % this->_models.size();
		if (GameObjectManager::collidesWith(box, _type) == fire)
			_isDying = true;
	}
}

void Goomba::newDirection()
{
	if (_directionGen == 1 || _directionGen == 2)
		_directionGen = rand() % 2 + 3;
	else if (_directionGen == 3 || _directionGen == 4)
		_directionGen = rand() % 2 + 1;
}

void Goomba::movement(float degree, float moveX, float moveY, float boxX, float boxY, BoundingBox & box)
{
	if (_direction != degree)
		Rotate(degree);
	box.x1 += boxX;
	box.x2 += boxX;
	box.y1 += boxY;
	box.y2 += boxY;
	if(GameObjectManager::collidesWith(box, _type) == grass)
		Move(moveX, moveY, 0);
	if (GameObjectManager::collidesWith(box, _type) == unbreakableBlocks || GameObjectManager::collidesWith(box, _type) == breakableBlocks)
		newDirection();
}

void Goomba::Move(float x, float y, float z)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Move(x, y, z);
	_totalElapsed = 0.0f;
}

void Goomba::Rotate(float degrees)
{
	if (_direction != degrees)
	{
		_direction = degrees;
		for (size_t i = 0; i < this->_models.size(); i++)
			this->_models[i]->Rotate(degrees);
		_totalElapsed = 0.0f;
	}
}