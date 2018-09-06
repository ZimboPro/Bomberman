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

	Player(ModelTexture & texture, float x, float y);

	void Update(float & timeElapsed);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};

#endif //BOMBERMAN_PLAYER_HPP
