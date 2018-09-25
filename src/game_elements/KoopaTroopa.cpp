//
// Created by Patrick RUSSELL on 2018/09/10.
//
#include "game_elements/KoopaTroopa.hpp"
#include "Game.hpp"

#include "ServiceLocator.hpp"

KoopaTroopa::KoopaTroopa(): _speed(2)
{
	_type = koopaTroopa;
}

KoopaTroopa::KoopaTroopa(KoopaTroopa const & src)
{
	*this = src;
}

KoopaTroopa::KoopaTroopa(Model_Texture & texture, float x, float y): VisibleGameObject(texture, x, y, true, false)
{
	_type = koopaTroopa;
}

KoopaTroopa::~KoopaTroopa() {}


void KoopaTroopa::Update(float & timeElapsed)
{
}
