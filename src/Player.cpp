//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

Player::Player(): _velocity(0), _maxVelocity(600.0f)
{
}

Player::Player(Model *model, float x, float y): _velocity(0), _maxVelocity(600.0f)
{
	VisibleGameObject::VisibleGameObject(model, x, y, true);
}

Player::~Player() {}


float Player::getVelocity() const
{
	return _velocity;
}

void Player::Update(float & timeElapsed)
{
//	if (Game::getInput() == sf::Keyboard::Left)
//	{
//		_velocity -= 3.0f;
//	}
//	else if (Game::getInput() == sf::Keyboard::Right)
//	{
//		_velocity += 3.0f;
//	}
//	else if (Game::getInput() == sf::Keyboard::Down)
//	{
//		_velocity = 0.0f;
//	}
//
//	if (_velocity > _maxVelocity)
//		_velocity = _maxVelocity;
//	else if (_velocity < -_maxVelocity)
//		_velocity = -_maxVelocity;
//
//	sf::Vector2f pos = this->getPosition();
//
//	if(pos.x < getSprite().getRadius() || pos.x > Game::getWindowSize().x)
//	{
//		_velocity = -_velocity;
//	}
//
//	getSprite().move(_velocity * timeElapsed, 0);
}