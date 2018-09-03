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

	void Update(float & timeElapsed);
	void Draw();

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};

#endif //BOMBERMAN_PLAYER_HPP
