//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "game_elements/VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		 _isLoaded(false), _type(grass), _isDying(false), _timeTodie(2), _timeSpentDying(0), _totalElapsedTime(0)
{}

VisibleGameObject::VisibleGameObject(VisibleGameObject const & src)
{
	*this = src;
}

VisibleGameObject::VisibleGameObject(Model_Texture & texture, float x, float y, bool collidable = true, bool isBreakable = false):
		_isLoaded(true), _isCollidable(collidable), _isBreakable(isBreakable), _timeTodie(2), _speed(2)
{
	_model.LoadModel_Texture(texture);
	_model.Position(x, y);
	_model.Scale(0.032f);
	_totalElapsedTime = 0;
	_direction = 0;
	_timeSpentDying = 0;
	_isDying = false;
}

BoundingBox VisibleGameObject::getBoundingBox()
{}

void VisibleGameObject::setDirection(float direction)
{
	if (_direction != direction)
	{
		_model.Rotate(direction);
		_direction = direction;
	}
}

void VisibleGameObject::kill()
{
	_isDying = true;
}

void VisibleGameObject::setScale(float scale)
{
	_model.Scale(scale);
}

VisibleGameObject::~VisibleGameObject()
{}

void	VisibleGameObject::Draw(Shaders & shader)
{
	if(_model.IsLoaded())
		_model.Draw(shader);
}

void VisibleGameObject::dying(float & elapsedTime)
{}

glm::vec3 VisibleGameObject::getPosition()
{
	return _model.GetPosition();
}

Model_Sprite VisibleGameObject::getModelSprite()
{
	return _model;
}

void	VisibleGameObject::setPosition(float x, float y, float z)
{
	_model.Position(x, y, z);
}

void	VisibleGameObject::Update(float & elapsedTime)
{
}

bool	VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}

bool	VisibleGameObject::isBreakable() const
{
	return _isBreakable;
}

objectTypes	VisibleGameObject::getType()
{
	return _type;
}

Rectangle VisibleGameObject::getBoundBox()
{
	return this->_model.getBoundingRectangle();
}

bool VisibleGameObject::Collision(Rectangle box)
{
	return this->_model.isColliding(box);
}