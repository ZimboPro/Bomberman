//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "game_elements/VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		 _isLoaded(false) {
	_type = grass;
}

VisibleGameObject::VisibleGameObject(VisibleGameObject const & src)
{
	*this = src;
}

VisibleGameObject::VisibleGameObject(Model_Texture & texture, float x, float y, bool collidable = true, bool isBreakable = false):
		_isLoaded(true), _isCollidable(collidable), _isBreakable(isBreakable)
{
	_model.LoadModel_Texture(texture);
	_model.Position(x, y);
	_model.Scale(0.032f);
	_direction = 0;
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

void VisibleGameObject::die()
{
	_isLoaded = false;
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
