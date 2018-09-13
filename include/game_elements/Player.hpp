//
// Created by Patrick RUSSELL on 2018/08/23.
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "VisibleGameObject.hpp"

class Player: public VisibleGameObject
{
public:
	~Player();
	Player();

	Player(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);
	BoundingBox getBoundingBox();
	void dropBomb();

	float getVelocity() const;

private:
	float _speed;
	float _maxVelocity;
};

#endif //BOMBERMAN_PLAYER_HPP
