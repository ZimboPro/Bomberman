//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_GOOMBA_H
#define BOMBERMAN_GOOMBA_H

#include "VisibleGameObject.hpp"

class Goomba: public VisibleGameObject
{
public:
	~Goomba();
	Goomba();

	Goomba(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};

#endif //BOMBERMAN_GOOMBA_H
