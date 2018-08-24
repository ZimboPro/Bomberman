//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Game.hpp"

Player::Player(): _velocity(0), _maxVelocity(600.0f)
{
	Load("player");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getRadius(), getSprite().getRadius());
}

Player::~Player() {}

void Player::Draw(sf::RenderWindow & window)
{
	VisibleGameObject::Draw(window);
}

float Player::getVelocity() const
{
	return _velocity;
}

void Player::Update(float & timeElapsed)
{
	if (Game::getInput() == sf::Keyboard::Left)
	{
		_velocity -= 3.0f;
	}
	else if (Game::getInput() == sf::Keyboard::Right)
	{
		_velocity += 3.0f;
	}
	else if (Game::getInput() == sf::Keyboard::Down)
	{
		_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;
	else if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->getPosition();

	if(pos.x < getSprite().getRadius() || pos.x > Game::getWindowSize().x)
	{
		_velocity = -_velocity;
	}

	getSprite().move(_velocity * timeElapsed, 0);
}