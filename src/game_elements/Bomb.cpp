//
// Created by Patrick RUSSELL on 2018/09/13.
//

#include <GameObjectManager.hpp>
#include "game_elements/Bomb.hpp"

Bomb::Bomb(): _timeTillExplode(5.0)
{
	_type = bomb;
}

Bomb::Bomb(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_timeTillExplode = 2;
}

Bomb::~Bomb()
{
	std::cout << "Bomb destructor called" << std::endl;
}


void Bomb::Update(float & timeElapsed)
{
	if (_timeTillExplode > 0)
		_timeTillExplode -= timeElapsed;
	else
	{
		GameObjectManager::explodeBomb(this);
		std::cout << "bomb exploded" << std::endl;
	}
}
