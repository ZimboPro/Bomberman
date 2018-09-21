//
// Created by Patrick RUSSELL on 2018/09/10.
//
#include "game_elements/KoopaTroopa.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"

KoopaTroopa::KoopaTroopa(): _velocity(0), _maxVelocity(600.0f)
{
	_type = koopaTroopa;
}

KoopaTroopa::KoopaTroopa(KoopaTroopa const & src)
{
	*this = src;
}

KoopaTroopa::KoopaTroopa(Model_Texture & texture, float x, float y): _velocity(0), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
	_type = koopaTroopa;
}

KoopaTroopa::~KoopaTroopa() {}


float KoopaTroopa::getVelocity() const
{
	return _velocity;
}

void KoopaTroopa::Update(float & timeElapsed)
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
