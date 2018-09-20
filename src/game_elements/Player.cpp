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
	_type = player;
	
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

	_box.x1 = static_cast<float>(_model.GetPosition().x);
	_box.x2 = static_cast<float>(_model.GetPosition().x + modelSize);

	_box.y1 = static_cast<float>(_model.GetPosition().z);
	_box.y2 = static_cast<float>(_model.GetPosition().z + modelSize);

	return _box;
}



// void Player::Update(float & timeElapsed)
// {
// 	float displacement = timeElapsed * _speed;
// 	glm::vec3 pos = _model.GetPosition();
// 	BoundingBox box = this->getBoundingBox();
// 	float moveToX;
// 	float moveToY;
// 	int randomNumGen = (std::rand() % (4 + 1 - 1)) + 1;

// 	if (randomNumGen == 1)
// 	{
// 		if (_direction != 270) {
// 			_model.Rotate(270);
// 			_direction = 270;
// 		}
// 		box.x1 -= displacement;
// 		box.x2 -= displacement;
// 		if(GameObjectManager::collidesWith(box) == grass)
// 			_model.Move(0 - displacement, 0);
// 	}
// 	else if (randomNumGen == 2)
// 	{
// 		if (_direction != 90) {
// 			_model.Rotate(90);
// 			_direction = 90;
// 		}
// 		box.x1 += displacement + 5.2;
// 		box.x2 += displacement + 5.2;
// 			if(GameObjectManager::collidesWith(box) == grass)
// 		_model.Move(0 + displacement, 0);
// 	}
// 	else if (randomNumGen == 3)
// 	{
// 		if (_direction != 0) {
// 			_model.Rotate(0);
// 			_direction = 0;
// 		}
// 		box.y1 += displacement + 5.2;
// 		box.y2 += displacement + 5.2;
// 			if(GameObjectManager::collidesWith(box) == grass)
// 		_model.Move(0 , 0 + displacement);
// 	}
// 	else if (randomNumGen == eKeys::Right)
// 	{
// 		if (_direction != 180) {
// 			_model.Rotate(180);
// 			_direction = 180;
// 		}
// 		box.y1 -= displacement;
// 		box.y2 -= displacement;
// 			if(GameObjectManager::collidesWith(box) == grass)
// 		_model.Move(0 , 0 - displacement);
// 	}
// 	Game::_camera.LookAt(_model.GetPosition());
// }

void Player::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();
	BoundingBox box = this->getBoundingBox();
	float moveToX;
	float moveToY;
	

	for (float i = 0; i < displacement; i += 0.01)
	{
		if (_direction == 270)
			_model.Move(0 - 0.009, 0);
		else if (_direction == 90)
			_model.Move(0 + 0.009, 0);
		else if (_direction == 0)
			_model.Move(0 , 0 + 0.009);
		else if (_direction == 180)
			_model.Move(0 , 0 - 0.009);

	}

	if (GameObjectManager::collidesWith(box) != grass)
	{
		// std::cout << "Direction: " << _direction << std::endl;
		if (_direction == 270)
			_model.Rotate(90);
		else if (_direction == 90)
			_model.Rotate(270);
		else if (_direction == 0)
			_model.Rotate(180);
		else if (_direction == 180)
			_model.Rotate(0);
		box.x1 -= displacement;
		box.x2 -= displacement;
		
	}


	if (Game::keyPressed() == eKeys::Up)
	{
		// for (int i = 0; i < 30; i++)
		// {
			if (_direction != 270) 
			{
				_model.Rotate(270);
				_direction = 270;
			}
			// box.x1 -= displacement;
			// box.x2 -= displacement;
			
			// if(GameObjectManager::collidesWith(box) == grass)
			// {
			// 	float movement = 0;
			// 	for (float i = 0; i < displacement * 2; i+=0.001)
			// 	{
			// 		if (movement < displacement * 2)
			// 		{
			// 			movement += 0.01;
			// 			_model.Move(0 - 0.01, 0);
			// 		}
			// 	}
			// 	std::cout << "Displacement: " << displacement << '\n';
			// 	usleep(1000);
			// }
			// }
		

				 /*for(int j = 0; j < 1000000; j++)
					std::cout << "wait\n";
				std::cout << "Move up\n";*/
			//	_model.Move(0 - displacement, 0);

			// 	}
			// }
			
		// std::cout << "=================================" << std::endl;
		// std::cout << "Direction: " << _direction << '\n';
		// std::cout << "Time elapsed: " << timeElapsed << '\n';
		// std::cout << "Speed: " << _speed << '\n';
		// std::cout << "Displacement: " << displacement << '\n';
		// std::cout << "=================================" << std::endl;
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		if (_direction != 90) {
			_model.Rotate(90);
			_direction = 90;
		}
		// box.x1 += displacement + 0.2;
		// box.x2 += displacement + 0.2;
		// 	if(GameObjectManager::collidesWith(box) == grass)
		// _model.Move(0 + displacement, 0);
		// std::cout << "=================================" << std::endl;
		// std::cout << "Direction: " << _direction << '\n';
		// std::cout << "Time elapsed: " << timeElapsed << '\n';
		// std::cout << "Speed: " << _speed << '\n';
		// std::cout << "Displacement: " << displacement << '\n';
		// std::cout << "=================================" << std::endl;
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		if (_direction != 0) {
			_model.Rotate(0);
			_direction = 0;
		}
		// box.y1 += displacement + 0.2;
		// box.y2 += displacement + 0.2;
		// 	if(GameObjectManager::collidesWith(box) == grass)
		// _model.Move(0 , 0 + displacement);
		// std::cout << "=================================" << std::endl;
		// std::cout << "Direction: " << _direction << '\n';
		// std::cout << "Time elapsed: " << timeElapsed << '\n';
		// std::cout << "Speed: " << _speed << '\n';
		// std::cout << "Displacement: " << displacement << '\n';
		// std::cout << "=================================" << std::endl;
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		if (_direction != 180) {
			_model.Rotate(180);
			_direction = 180;
		}
		// box.y1 -= displacement;
		// box.y2 -= displacement;
		// 	if(GameObjectManager::collidesWith(box) == grass)
		// _model.Move(0 , 0 - displacement);
		// std::cout << "=================================" << std::endl;
		// std::cout << "Direction: " << _direction << '\n';
		// std::cout << "Time elapsed: " << timeElapsed << '\n';
		// std::cout << "Speed: " << _speed << '\n';
		// std::cout << "Displacement: " << displacement << '\n';
		// std::cout << "=================================" << std::endl;
	}
	
	Game::_camera.LookAt(_model.GetPosition());
}