//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		_shader(NULL), _model(NULL), _isLoaded(false) {}

VisibleGameObject::VisibleGameObject(Model *model, Shaders *shader, float y, float x, bool collidable = true):
		_model(model), _shader(shader), _isLoaded(true), _isCollidable(collidable)
{
	_position.x = x;
	_position.y = y;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::setShader(Shaders *shader)
{
	this->_shader = shader;
	if (_model && _shader)
		_isLoaded = true;
}

void VisibleGameObject::setModel(Model *model)
{
	this->_model = model;
	if (_model && _shader)
		_isLoaded = true;
}

void VisibleGameObject::Draw()
{
	if(this->_isLoaded)
	{
		_model->Draw(*_shader);
	}
}

glm::vec2 VisibleGameObject::getPosition()
{
	return _position;
}

void VisibleGameObject::setPosition(int y, int x)
{
	_position.x = x;
	_position.y = y;
}

void VisibleGameObject::Update(float & elapsedTime)
{
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}
