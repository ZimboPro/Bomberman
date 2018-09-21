//
// Created by Patrick RUSSELL on 2018/09/10.
//

#include "game_elements/powerBlock.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

PowerBlock::PowerBlock(): _speed(2)
{
	_type = powerBlock;
}

PowerBlock::PowerBlock(PowerBlock const & src)
{
	*this = src;
}

PowerBlock::PowerBlock(Model_Texture & texture, float x, float y): _speed(2), VisibleGameObject(texture, x, y, true, false)
{
	_type = powerBlock;
}

PowerBlock::~PowerBlock() {}

void PowerBlock::Update(float & timeElapsed)
{
}
