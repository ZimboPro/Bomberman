//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include "Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "eKeys.hpp"

Player::Player(): _speed(0), _maxVelocity(600.0f)
{
}

Player::Player(Model_Texture & texture, float x, float y): _speed(2.0f), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
}

Player::~Player() {}


void Player::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();
//	std::cout << "Player x " << pos.x << " y " << pos.z << " " << std::endl;
//	std::cout << "Displacement: " << displacement << std::endl;
//	std::cout << "elapsed time: " << timeElapsed << std::endl;
//Game::keyPressed() == eKeys::Up
	if (Game::keyPressed() == eKeys::Up)
	{

		_model.Move(0 - displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		_model.Move(0 + displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		_model.Move(0 , 0 + displacement);
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		_model.Move(0 , 0 - displacement);
	}
}