//
// Created by Patrick RUSSELL on 2018/08/23.
//

#include <cassert>
#include <cstdlib>
#include <Error.hpp>
#include "game_elements/Player.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"
#include "eKeys.hpp"
#include <ctime>
#include <unistd.h>

Player::Player(): _speed(3.0f)
{
	init();
}

Player::Player(Player const & src)
{
	init();
	*this = src;
}

Player::Player(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false), _speed(3.0f)
{
	init();
}

Player::Player(std::vector<Model_Texture *> & textures, float x, float y): _speed(3.0f)
{
	init();
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[1]));
	_models.emplace_back(new Model_Sprite(*textures[0]));
	_models.emplace_back(new Model_Sprite(*textures[2]));

	for (size_t i = 0; i < this->_models.size(); i++)
	{
		this->_models[i]->Position(x, y);
		this->_models[i]->Scale(0.032f);
	}
}

Player::~Player()
{
	for (size_t i = 0; i < this->_models.size(); i++)
		delete this->_models[i];
}

void Player::init()
{
	VisibleGameObject::_isBreakable = false;
	VisibleGameObject::_isLoaded = true;
	VisibleGameObject::_isCollidable = true;
	_index = 0;
	_prevIndex = 0;
	_totalElapsed = 0.0f;
	_type = player;
	_totalDroppedWhilstDying = 0;
	_timeTodie = 4;
	_timeSpentDying = 0;
	_timeSpawned = 0.0f;
	_direction = 0;
	_wonLevel = false;
	_spawned = false;
	_isDying = false;
	_spawn = false;
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
}

BoundingBox Player::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Player object not loaded");

	float modelSize = 0.6f;
	glm::vec3 pos = _models[0]->GetPosition();

	_box.x1 = pos.x;
	_box.x2 = pos.x + modelSize;

	_box.y1 = pos.z;
	_box.y2 = pos.z + modelSize;

	return _box;
}

void Player::placeBombX(float & bombX, float & bombY, float bombOffset, float moveX, float moveY, float pos, bool ceil)
{
	if (ceil)
		bombX = ceilf(bombX + bombOffset);
	else
		bombX = floor(bombX + bombOffset);

	if (abs(bombX - pos) < 0.5)
		Move(moveX, moveY);
	bombY = round(bombY);
}

void Player::placeBombY(float & bombX, float & bombY, float bombOffset, float moveX, float moveY, float pos, bool ceil)
{
	if (ceil)
		bombY = ceilf(bombY + bombOffset);
	else
		bombY = floor(bombY + bombOffset);
	
	if (abs(bombY - pos) < 0.3) // comparrison between player y and bomb y
		Move(moveX, moveY);
	
	bombX = round(bombX);
}

void Player::dropBomb()
{
	glm::vec3 pos = _models[0]->GetPosition();
	float bombOffset = 0.5;
	float playerOffset = 0.3;
	float bombX = pos.x;
	float bombY = pos.z;
	if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/gameplay/drop_bomb.wav");
	if (_direction == 270) // UP
		placeBombX(bombX, bombY, -bombOffset, 0.0f, playerOffset, pos.x, false);
	else if (_direction == 90) // Down
		placeBombX(bombX, bombY, bombOffset, 0.0f, -playerOffset, pos.x, true);
	else if (_direction == 0) // Left
		placeBombY(bombX, bombY, bombOffset, playerOffset, 0.0f, pos.z, true);
	else if (_direction == 180) // Right
		placeBombY(bombX, bombY, -bombOffset, -playerOffset, 0.0f, pos.z, false);
	GameObjectManager::addDynamicObject(bomb, bombX ,bombY);
}

void Player::Draw(Shaders & shader)
{
	if(_models[_index]->IsLoaded())
		_models[_index]->Draw(shader);
}

void Player::dying(float & elapsedTime)
{
	float rotationMultiplier = 150;
	setCamera();
	if(_timeSpentDying < _timeTodie)
	{
		_timeSpentDying += elapsedTime;
		Move(0, 0, (-elapsedTime * _speed) / _timeTodie);
		_totalDroppedWhilstDying += (elapsedTime * _speed) / _timeTodie;
		Rotate(_timeSpentDying * _speed * rotationMultiplier);
	}
	else
	{
		glm::vec3 pos = _models[0]->GetPosition();
		GameInterface::adjustLives(-1);
		GameInterface::resetRangeMultiplier();
		Move(-(pos.x - Map::getPlayerStartX()), -(pos.z - Map::getPlayerStartY()), _totalDroppedWhilstDying);
		setCamera();
		fixCameraPosition();
		Rotate(0);
		_totalDroppedWhilstDying = 0;
		_isDying = false;
		_spawned = false;
		_timeSpawned = 0.0f;
		_timeSpentDying = 0;
		_sound->stopAllSounds();
		if (Game::_settings.music && GameInterface::stillAlive())
			_sound->playSong("../../Assets/sounds/background_music/gameplay_background_track.wav", true);
	}
}

void Player::movement(float degree, float x, float y, float x1, float y1, float camX, float camY, BoundingBox & box, objectTypes &collidesWith, float timeElapsed)
{
	Rotate(degree);
	box.x1 += x;
	box.x2 += x;
	box.y1 += y;
	box.y2 += y;
	if((collidesWith = GameObjectManager::collidesWith(box, _type)) == grass)
	{
		_totalElapsed += timeElapsed;
		Game::_camera.Move(camX, camY);
		if (_totalElapsed > 0.13f)
			Move(x + x1, y + y1);
	}
}

void Player::checks(float &timeElapsed)
{
	if (!_spawn)
	{
		setCamera();
		Game::_camera.LookAt(_models[_index]->GetPosition());
		fixCameraPosition();
		_spawn = true;
	}
	if(_isDying)
		dying(timeElapsed);
	if (!_spawned && !_isDying)
	{
		_timeSpawned += timeElapsed;
		if (_timeSpawned > 2.0f)
		{
			_spawned = true;
			_timeSpawned = 0.0f;
		}
	}

	if (_wonLevel)
		GameInterface::setLevelCompleted(true);
}

void Player::Update(float & timeElapsed)
{
	checks(timeElapsed);
	if (_isDying)
		return;
	float camDisplacement = timeElapsed * _speed;
	BoundingBox box = this->getBoundingBox();
	_prevIndex = _index;
	float displacement = _totalElapsed * _speed;
	glm::vec3 pos = _models[0]->GetPosition();

	float alignX = round(pos.x) - pos.x;
	float alignY = round(pos.z) - pos.z;

	objectTypes collidesWith = grass;

	if (Game::keyPressed() == eKeys::Up)
		movement(270.0f, -displacement, alignY, 0.0f, 0.0f, -camDisplacement, 0.0f, box, collidesWith, timeElapsed);
	else if (Game::keyPressed() == eKeys::Down)
		movement(90.0f, displacement + 0.1, alignY, -0.1f, 0.0f, camDisplacement, 0.0f, box, collidesWith, timeElapsed);
	else if (Game::keyPressed() == eKeys::Left)
		movement(0.0f, alignX, displacement + 0.1, 0.0f, -0.1f, 0.0f, camDisplacement, box, collidesWith, timeElapsed);
	else if (Game::keyPressed() == eKeys::Right)
		movement(180.0f, alignX, -displacement, 0.0f, 0.0f, 0.0f, -camDisplacement, box, collidesWith, timeElapsed);
	else if (Game::keyPressed() == eKeys::Undefined)
		_index = 0;

	switch (collidesWith)
	{
		case fire:
			std::cout << "Player - Fire\n";
			aboutToDie();
			break;
		case gate:
			if(GameInterface::allEnemiesDead())
			{
				_wonLevel = true;
				if (Game::_settings.sound)
					_sound->playSound("../../Assets/sounds/gameplay/jump_into_pipe.wav");
			}
			break;
		default:
			break;
	}
	fixCameraPosition();
	if (Game::keyTyped() == eKeys::Place && !_isDying)
		dropBomb();
}

void Player::aboutToDie()
{
	if (_spawned)
	{
		_isDying = true;
		_sound->stopAllSounds();
		if (Game::_settings.music)
			_sound->playSong("../../Assets/sounds/gameplay/mario_dies.wav", false);
	}
}

void Player::Move(float x, float y, float z)
{
	for (size_t i = 0; i < this->_models.size(); i++)
		this->_models[i]->Move(x, y, z);
	if (_prevIndex == _index)
		_index = (_index + 1) % this->_models.size();
	_totalElapsed = 0.0f;
}

void Player::Rotate(float degrees)
{
	if (_direction != degrees)
	{
		_direction = degrees;
		for (size_t i = 0; i < this->_models.size(); i++)
			this->_models[i]->Rotate(degrees);
		if (_prevIndex == _index)
			_index = (_index + 1) % this->_models.size();
		_totalElapsed = 0.0f;
	}
}

void Player::setCamera()
{
	Game::_camera.Position = this->_models[_index]->GetPosition() + glm::vec3(15.0f, 25.0f, 0.0f);
	Game::_camera.Zoom = 20.0f;
}

void Player::fixCameraPosition()
{
	glm::vec3 posPlayer = this->_models[_index]->GetPosition();
	if (posPlayer.x <= 6.25f || Game::_camera.Position.x < 21.25f)
		Game::_camera.Position.x = 21.25f;
	else if (posPlayer.x >= 10.0f || Game::_camera.Position.x > 25.0f)
		Game::_camera.Position.x = 25.0f;

	if (posPlayer.z <= 5.5f || Game::_camera.Position.z < 5.5f)
		Game::_camera.Position.z = 5.5f;
	else if (posPlayer.z >= 25.0f || Game::_camera.Position.z > 25.0f)
		Game::_camera.Position.z = 25.0f;
}

Rectangle Player::getBoundBox()
{
	Rectangle temp = this->_models[0]->getBoundingRectangle();
	glm::vec3 pos = this->_models[0]->GetPosition();
	temp.x1 -= pos.x;
    temp.x2 -= pos.x;
    temp.y1 -= pos.z;
    temp.y2 -= pos.z;
	float percentage = 0.25f;
	temp.x1 *= percentage;
    temp.x2 *= percentage;
    temp.y1 *= percentage;
    temp.y2 *= percentage;
	temp.x1 += pos.x;
    temp.x2 += pos.x;
    temp.y1 += pos.z;
    temp.y2 += pos.z;
	return temp;
}
