//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <glm/vec3.hpp>
#include "VisibleGameObject.hpp"

VisibleGameObject::VisibleGameObject():
		_shader(null), _model(null), _isLoaded(false) {}

VisibleGameObject::VisibleGameObject(Shaders *shader, Model *model, float y, float x):
		_shader(shader), _model(model), _isLoaded(true) {}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::setShader(Shader *shader)
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

void VisibleGameObject::setPosition(int x, int y)
{
	if(this->_isLoaded)
	{
	}
}

void VisibleGameObject::Update(float & elapsedTime)
{
}

//sf::CircleShape & VisibleGameObject::getSprite()
//{
//	return _sprite;
//}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::getWidth()
{
//	return _sprite.getRadius() * 2;
}

float VisibleGameObject::getHeight()
{
//	return _sprite.getRadius() * 2;
}

sf::Rect<float> VisibleGameObject::getBoundingRect()
{
	sf::Vector2f pos = _sprite.getPosition();
	glm::vec3 ble()

	return sf::Rect<float>(
			pos.x - _sprite.getRadius(),
			pos.y - _sprite.getRadius(),
			_sprite.getRadius() * 2,
			_sprite.getRadius() * 2
			);
}
