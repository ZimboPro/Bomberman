//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		 _model(NULL), _isLoaded(false) {}

VisibleGameObject::VisibleGameObject(Model *model, float x, float y, bool collidable = true):
		_model(model), _isLoaded(true), _isCollidable(collidable), _isBreakable(false)
{
	_position.x = x;
	_position.y = y;
	_position.z = 0;
}

VisibleGameObject::~VisibleGameObject()
{
}


void	VisibleGameObject::setModel(Model *model)
{
	this->_model = model;
	if (_model)
		_isLoaded = true;
}

void	VisibleGameObject::Draw(Shaders & shader)
{
	if(this->_isLoaded)
	{
		_model->DrawAt(shader, _position.x, _position.y, _position.z);
	}
}

glm::vec3 VisibleGameObject::getPosition()
{
	return _position;
}

Model * VisibleGameObject::getModel()
{
	return _model;
}

void	VisibleGameObject::setPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
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
