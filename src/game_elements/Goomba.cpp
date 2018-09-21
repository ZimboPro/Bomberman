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
}

Goomba::Goomba(Model_Texture & texture, float x, float y): _speed(3), VisibleGameObject(texture, x, y, true, false)
{
	_type = goomba;
	_time = glfwGetTime();
}

Goomba::Goomba(Goomba const & src)
{
	*this = src;
	_time = glfwGetTime();
}


Goomba::~Goomba() {}

BoundingBox Goomba::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Goomba object not loaded");

	float modelSize = 0.6f;

	_box.x1 = static_cast<float>(_model.GetPosition().x);
	_box.x2 = static_cast<float>(_model.GetPosition().x + modelSize);

	_box.y1 = static_cast<float>(_model.GetPosition().z);
	_box.y2 = static_cast<float>(_model.GetPosition().z + modelSize);

	return _box;
}

// void Goomba::Delay(void)
// {
// 	// _directionGen = rand() % 4 + 1;
// 	BoundingBox box = this->getBoundingBox();


// 	clock_t start_time = clock();
//     clock_t end_time = 1000 + start_time;
//     while(clock() != end_time);
// }

void ShiftBox(BoundingBox & box, float x, float y)
{
	box.x1 += x;
	box.x2 += x;
	box.y1 += y;
	box.y2 += y;
}

void Goomba::RandomDirection()
{
	// glm::vec3 temp = this->_model.GetPosition();
	// float shift = 0.82f;
	// if (fmod(temp.x + shift, 1.64) > 0.8f && fmod(temp.x + shift, 1.64) < 0.84f &&
	// 	fmod(temp.z + shift, 1.64) > 0.8f && fmod(temp.z + shift, 1.64) > 0.84f)
	// {
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
			if (GameObjectManager::collidesWith(boxLeft) != unbreakableBlocks && GameObjectManager::collidesWith(boxLeft) != breakableBlocks)
				dir.push_back(3);
			//right
			if (GameObjectManager::collidesWith(boxRight) != unbreakableBlocks && GameObjectManager::collidesWith(boxRight) != breakableBlocks)
				dir.push_back(4);
			//up
			if (GameObjectManager::collidesWith(boxUp) != unbreakableBlocks && GameObjectManager::collidesWith(boxUp) != breakableBlocks)
				dir.push_back(1);
			//down
			if (GameObjectManager::collidesWith(boxDown) != unbreakableBlocks && GameObjectManager::collidesWith(boxDown) != breakableBlocks)
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

void Goomba::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();
	BoundingBox box = this->getBoundingBox();
	int newDir;
	// float moveToX;
	// float moveToY;
	
	// Delay();

	// for (int i = 0; i < 10; i++)
	// {
		RandomDirection();
		if (_directionGen == 1)
		{
			if (_direction != 270)
			{
				_model.Rotate(270);
				_direction = 270;
			}
			box.x1 -= displacement;
			box.x2 -= displacement;
			if(GameObjectManager::collidesWith(box) == grass)
				_model.Move(0 - displacement, 0);
			if (GameObjectManager::collidesWith(box) == unbreakableBlocks || GameObjectManager::collidesWith(box) == breakableBlocks)
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
			{
				_model.Rotate(90);
				_direction = 90;
			}
			box.x1 += displacement + 0.2;
			box.x2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box) == grass)
				_model.Move(0 + displacement, 0);
			if (GameObjectManager::collidesWith(box) == unbreakableBlocks || GameObjectManager::collidesWith(box) == breakableBlocks)
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
			{
				_model.Rotate(0);
				_direction = 0;
			}
			box.y1 += displacement + 0.2;
			box.y2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box) == grass)
				_model.Move(0 , 0 + displacement);
			if (GameObjectManager::collidesWith(box) == unbreakableBlocks || GameObjectManager::collidesWith(box) == breakableBlocks)
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
			{
				_model.Rotate(180);
				_direction = 180;
			}
			box.y1 -= displacement;
			box.y2 -= displacement;
			if(GameObjectManager::collidesWith(box) == grass)
				_model.Move(0 , 0 - displacement);
			if (GameObjectManager::collidesWith(box) == unbreakableBlocks || GameObjectManager::collidesWith(box) == breakableBlocks)
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
	// }
	
	Game::_camera.LookAt(_model.GetPosition());
}