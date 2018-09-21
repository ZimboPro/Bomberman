//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/Goomba.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "Error.hpp"

Goomba::Goomba(): _speed(3)
{
	_type = goomba;
}

Goomba::Goomba(Model_Texture & texture, float x, float y): _speed(3), VisibleGameObject(texture, x, y, true, false)
{
	_type = goomba;
}

Goomba::Goomba(Goomba const & src)
{
	*this = src;
}


Goomba::~Goomba() {}

BoundingBox Goomba::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Player object not loaded");

	float modelSize = 0.6f;

	_box.x1 = static_cast<float>(_model.GetPosition().x);
	_box.x2 = static_cast<float>(_model.GetPosition().x + modelSize);

	_box.y1 = static_cast<float>(_model.GetPosition().z);
	_box.y2 = static_cast<float>(_model.GetPosition().z + modelSize);

	return _box;
}

void Goomba::Update(float & timeElapsed)
{
	float displacement = timeElapsed * _speed;
	glm::vec3 pos = _model.GetPosition();
	BoundingBox box = this->getBoundingBox();
	float moveToX;
	float moveToY;

	if (Game::keyPressed() == eKeys::Up)
	{
		if (_direction != 270) {
			_model.Rotate(270);
			_direction = 270;
		}
		box.x1 -= displacement;
		box.x2 -= displacement;
		if(GameObjectManager::collidesWith(box) == grass)
			_model.Move(0 - displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Down)
	{
		if (_direction != 90) {
			_model.Rotate(90);
			_direction = 90;
		}
		box.x1 += displacement + 0.2;
		box.x2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box) == grass)
		_model.Move(0 + displacement, 0);
	}
	else if (Game::keyPressed() == eKeys::Left)
	{
		if (_direction != 0) {
			_model.Rotate(0);
			_direction = 0;
		}
		box.y1 += displacement + 0.2;
		box.y2 += displacement + 0.2;
			if(GameObjectManager::collidesWith(box) == grass)
		_model.Move(0 , 0 + displacement);
	}
	else if (Game::keyPressed() == eKeys::Right)
	{
		if (_direction != 180) {
			_model.Rotate(180);
			_direction = 180;
		}
		box.y1 -= displacement;
		box.y2 -= displacement;
			if(GameObjectManager::collidesWith(box) == grass)
		_model.Move(0 , 0 - displacement);
	}
	Game::_camera.LookAt(_model.GetPosition());
}