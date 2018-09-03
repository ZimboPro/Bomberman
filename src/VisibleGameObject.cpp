//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <glm/vec3.hpp>
#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		_shader(NULL), _model(NULL), _isLoaded(false) {}

VisibleGameObject::VisibleGameObject(Shaders *shader, Model *model, float y, float x):
		_shader(shader), _model(model), _isLoaded(true), _y(y), _x(x) {}

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
	}
}

void VisibleGameObject::setPosition(int y, int x)
{
	_x = x;
	_y = y;
}

void VisibleGameObject::Update(float & elapsedTime)
{
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::getWidth()
{
}

float VisibleGameObject::getHeight()
{
}

