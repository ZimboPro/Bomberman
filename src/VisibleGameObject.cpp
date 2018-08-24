//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject()
{
	this->_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject() {}

void VisibleGameObject::Load(std::string type)
{
	if (type == "player")
	{
		this->_sprite.setPointCount(3);
		this->_sprite.setRadius(20);
		//set origin
	}
	else if (type == "wall")
	{
		this->_sprite.setPointCount(4);
		this->_sprite.setRadius(30);
		//set origin
	}
	this->_isLoaded = true;
}

void VisibleGameObject::Draw(sf::RenderWindow & window)
{
	if(this->_isLoaded)
	{
		window.draw(_sprite);
	}
}

void VisibleGameObject::setPosition(int x, int y)
{
	if(this->_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::Update(float & elapsedTime)
{

}

sf::Vector2f VisibleGameObject::getPosition() const
{
	if(_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::CircleShape & VisibleGameObject::getSprite()
{
	return _sprite;
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}