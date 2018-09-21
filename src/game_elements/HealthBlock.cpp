//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/HealthBlock.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"

HealthBlock::HealthBlock(): _speed(2)
{
	_type = healthBlock;
}

HealthBlock::HealthBlock(HealthBlock const & src)
{
	*this = src;
}

HealthBlock::HealthBlock(Model_Texture & texture, float x, float y): _speed(2), VisibleGameObject(texture, x, y, true, false)
{
	_type = healthBlock;
}

HealthBlock::~HealthBlock() {}


void HealthBlock::Update(float & timeElapsed)
{
}
