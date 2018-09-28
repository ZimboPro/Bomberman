//
// Created by Patrick RUSSELL on 2018/09/20.
//

#ifndef BOMBERMAN_FIRE_HPP
#define BOMBERMAN_FIRE_HPP


#include "VisibleGameObject.hpp"
#include "ServiceLocator.hpp"

class Fire: public VisibleGameObject
{
public:
	Fire();
	Fire(Fire const & src);
	Fire(Model_Texture & texture, float x, float y);
	~Fire();

	void Update(float & timeElapsed);
	BoundingBox getBoundingBox();

	Fire & operator=(Fire const & rhs);

private:
	float _burnTime;
	IAudioProvider * _sound;
};


#endif //BOMBERMAN_FIRE_HPP
