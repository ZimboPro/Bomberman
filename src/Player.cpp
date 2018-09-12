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
//	std::cout << "Displacement: " << displacement << std::endl;
//	std::cout << "elapsed time: " << timeElapsed << std::endl;
//Game::keyPressed() == eKeys::Up
	if ( Game::_window.isKeyPressed(GLFW_KEY_UP))
	{
		_model.Move(0 - displacement, 0);
	}
	else if (Game::_window.isKeyPressed(GLFW_KEY_DOWN))
	{
		_model.Move(0 + displacement, 0);
	}
	else if (Game::_window.isKeyPressed(GLFW_KEY_LEFT))
	{
		_model.Move(0 , 0 + displacement);
	}
	else if (Game::_window.isKeyPressed(GLFW_KEY_RIGHT))
	{
		_model.Move(0 , 0 - displacement);
	}
}