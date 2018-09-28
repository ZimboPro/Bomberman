//
// Created by Patrick RUSSELL on 2018/09/10.
//
#include "game_elements/KoopaTroopa.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"


KoopaTroopa::KoopaTroopa()
{
	init();
}

KoopaTroopa::KoopaTroopa(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	init();
}

KoopaTroopa::KoopaTroopa(KoopaTroopa const & src)
{
	*this = src;
	init();
}

KoopaTroopa::KoopaTroopa(std::vector<Model_Texture *> & textures, float x, float y)
{
	init();
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[1]));
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[2]));
	_models.emplace_back(new Model_Sprite(*textures[3]));

	for (size_t i = 0; i < this->_models.size(); i++)
	{
		this->_models[i]->Position(x, y);
		this->_models[i]->Scale(0.032f);
	}
}

KoopaTroopa::~KoopaTroopa()
{
	for (size_t i = 0; i < this->_models.size(); i++)
		delete this->_models[i];
}

void KoopaTroopa::init()
{
	VisibleGameObject::_timeTodie = 2;
	VisibleGameObject::_isBreakable = false;
	VisibleGameObject::_isLoaded = true;
	VisibleGameObject::_isCollidable = true;
	VisibleGameObject::_isDying = false;
	
	_type = koopaTroopa;
	_time = glfwGetTime();
	_index = 0;
	_direction = 0;
	_totalElapsed = 0.0f;
	_directionGen = rand() % 4 + 1;
	_speed = 1.5;
	_timeSpentDying = 0;
}

BoundingBox KoopaTroopa::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("KoopaTroopa object not loaded");

	float modelSize = 0.6f;

	glm::vec3 pos = this->_models[_index]->GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

void KoopaTroopa::ShiftBox(BoundingBox & box, float x, float y)
{
	box.x1 += x;
	box.x2 += x;
	box.y1 += y;
	box.y2 += y;
}

void KoopaTroopa::CheckDirection(BoundingBox box, float x, float y, std::vector<int> & dir, int d)
{
	ShiftBox(box, - ( 2 * 0.8f), 0.0f);
	if (GameObjectManager::collidesWith(box, _type) != unbreakableBlocks && GameObjectManager::collidesWith(box, _type) != breakableBlocks)
		dir.push_back(d);
}

void KoopaTroopa::RandomDirection()
{
	if (glfwGetTime() - _time > 1)
	{
		BoundingBox box = this->getBoundingBox();

		std::vector<int> dir;
		//left
		CheckDirection(box, - ( 2 * 0.8f), 0.0f, dir, 3);
		//right
		CheckDirection(box, ( 2 * 0.8f), 0.0f, dir, 4);
		//up
		CheckDirection(box, 0.0f, - ( 2 * 0.8f), dir, 1);
		//down
		CheckDirection(box, 0.0f, ( 2 * 0.8f), dir, 2);
		if (dir.size() > 2)
		{
			int index = rand() % (100 * dir.size());
			_directionGen = dir[index / 100];
			_time = glfwGetTime();
		}
	}
}

void KoopaTroopa::dying(float & elapsedTime)
{
	if(_timeSpentDying < _timeTodie)
	{
		_timeSpentDying += elapsedTime;
		Move(0, 0, (-elapsedTime * _speed) / _timeTodie);
	}
	else
	{
		GameInterface::troopaKilled();
		GameInterface::adjustScore(20);
		_isLoaded = false;
		GameObjectManager::removeDynamicObject(this);
	}
	_index = this->_models.size() - 1;
}

void KoopaTroopa::Draw(Shaders & shader)
{
	if(_models[_index]->IsLoaded())
		_models[_index]->Draw(shader);
}

void KoopaTroopa::Update(float & timeElapsed)
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
		_index = (_index + 1) % (this->_models.size() - 1);
		if (GameObjectManager::collidesWith(box, _type) == fire)
			_isDying = true;
	}
}

void KoopaTroopa::newDirection()
{
	if (_directionGen < 3)
		_directionGen = rand() % 2 + 3;
	else
		_directionGen = rand() % 2 + 1;
}

void KoopaTroopa::movement(float degree, float moveX, float moveY, float boxX, float boxY, BoundingBox box)
{
	objectTypes collidesWith = grass;

	if (_direction != degree)
		Rotate(degree);
	box.x1 += boxX;
	box.x2 += boxX;
	box.y1 += boxY;
	box.y2 += boxY;
	if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
		Move(moveX, moveY, 0);
//	if (collidesWith == unbreakableBlocks || collidesWith == breakableBlocks || collidesWith == bomb)
	if (collidesWith == player)
		GameObjectManager::killPlayer();
	else if (collidesWith == fire)
		_isDying = true;
	else if (collidesWith != grass)
		newDirection();
}

void KoopaTroopa::Move(float x, float y, float z)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Move(x, y, z);
	_totalElapsed = 0.0f;
}

void KoopaTroopa::Rotate(float degrees)
{
	if (_direction != degrees)
	{
		_direction = degrees;
		for (size_t i = 0; i < this->_models.size(); i++)
			this->_models[i]->Rotate(degrees);
		_totalElapsed = 0.0f;
	}
}
