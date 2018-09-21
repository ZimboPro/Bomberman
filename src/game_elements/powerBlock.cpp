//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/powerBlock.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

PowerBlock::PowerBlock(): _velocity(0), _maxVelocity(600.0f)
{
	_type = powerBlock;
}

PowerBlock::PowerBlock(PowerBlock const & src)
{
	*this = src;
}

PowerBlock::PowerBlock(Model_Texture & texture, float x, float y): _velocity(0), _maxVelocity(600.0f), VisibleGameObject(texture, x, y, true, false)
{
	_type = powerBlock;
}

PowerBlock::~PowerBlock() {}


float PowerBlock::getVelocity() const
{
	return _velocity;
}

void PowerBlock::Update(float & timeElapsed)
{
}
