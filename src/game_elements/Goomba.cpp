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
	_type = goomba;
	_time = glfwGetTime();
	_index = 0;
}

Goomba::Goomba(Model_Texture & texture, float x, float y): _speed(3), VisibleGameObject(texture, x, y, true, false)
{
	_type = goomba;
	_time = glfwGetTime();
	_index = 0;
}

Goomba::Goomba(Goomba const & src)
{
	*this = src;
	_time = glfwGetTime();
}

Goomba::Goomba(std::vector<Model_Texture *> & textures, float x, float y) : _speed(3)
{
	_time = glfwGetTime();
	_timeTodie = 2;
	VisibleGameObject::_isBreakable = false;
	VisibleGameObject::_isLoaded = true;
	VisibleGameObject::_isCollidable = true;
	_isDying = false;
	_totalElapsed = 0.0f;
	_index = 0;
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[1]));
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[2]));
	_type = goomba;
	_timeSpentDying = 0;

	for (size_t i = 0; i < this->_models.size(); i++)
	{
		this->_models[i]->Position(x, y);
		this->_models[i]->Scale(0.032f);
	}
	_direction = 0;
}

Goomba::~Goomba()
{
	for (size_t i = 0; i < this->_models.size(); i++)
		delete this->_models[i];
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
	if (_isDying)
	{
		dying(timeElapsed);
<<<<<<< HEAD
		return;
=======
		return ;
>>>>>>> b0bfe583cd8db42ed1c24579a0531d38b41e0d7d
	}

	glm::vec3 pos = _models[_index]->GetPosition();
	BoundingBox box = getBoundingBox();
	int newDir;
	_totalElapsed += timeElapsed;

	if (_totalElapsed > 0.13f)
	{
		float displacement = _totalElapsed * _speed;
		RandomDirection();
		if (_directionGen == 1)
		{
			if (_direction != 270)
				Rotate(270);
			box.x1 -= displacement;
			box.x2 -= displacement;
			if(GameObjectManager::collidesWith(box, _type) == grass)
				Move(0 - displacement, 0, 0);
			if (GameObjectManager::collidesWith(box, _type) == unbreakableBlocks || GameObjectManager::collidesWith(box, _type) == breakableBlocks)
			{
				if (_directionGen == 1 || _directionGen == 2)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 3;
					else
						_directionGen = 4;
				}
				else if (_directionGen == 3 || _directionGen == 4)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 1;
					else
						_directionGen = 2;
				}
			}
		}
		else if (_directionGen == 2)
		{
			if (_direction != 90)
				Rotate(90);
			box.x1 += displacement + 0.2;
			box.x2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box, _type) == grass)
				Move(0 + displacement, 0, 0);
			if (GameObjectManager::collidesWith(box, _type) == unbreakableBlocks || GameObjectManager::collidesWith(box, _type) == breakableBlocks)
			{
				if (_directionGen == 1 || _directionGen == 2)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 3;
					else
						_directionGen = 4;
				}
				else if (_directionGen == 3 || _directionGen == 4)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 1;
					else
						_directionGen = 2;
				}
			}
		}
		else if (_directionGen == 3)
		{
			if (_direction != 0)
				Rotate(0);
			box.y1 += displacement + 0.2;
			box.y2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box, _type) == grass)
				Move(0 , 0 + displacement);
			if (GameObjectManager::collidesWith(box, _type) == unbreakableBlocks || GameObjectManager::collidesWith(box, _type) == breakableBlocks)
			{
				if (_directionGen == 1 || _directionGen == 2)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 3;
					else
						_directionGen = 4;
				}
				else if (_directionGen == 3 || _directionGen == 4)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 1;
					else
						_directionGen = 2;
				}
			}
		}
		else if (_directionGen == 4)
		{
			if (_direction != 180)
				Rotate(180);
			box.y1 -= displacement;
			box.y2 -= displacement;
			if(GameObjectManager::collidesWith(box, _type) == grass)
				Move(0 , 0 - displacement);
			if (GameObjectManager::collidesWith(box, _type) == unbreakableBlocks || GameObjectManager::collidesWith(box, _type) == breakableBlocks)
			{
				if (_directionGen == 1 || _directionGen == 2)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 3;
					else
						_directionGen = 4;
				}
				else if (_directionGen == 3 || _directionGen == 4)
				{
					newDir = rand() % 2 + 1;
					if (newDir == 1)
						_directionGen = 1;
					else
						_directionGen = 2;
				}
			}
		}
		_index = (_index + 1) % this->_models.size();
		if (GameObjectManager::collidesWith(box, _type) == fire)
			_isDying = true;
	}
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