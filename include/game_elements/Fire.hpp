//
// Created by Patrick RUSSELL on 2018/09/20.
//

#ifndef BOMBERMAN_FIRE_HPP
#define BOMBERMAN_FIRE_HPP


#include "VisibleGameObject.hpp"

class Fire: public VisibleGameObject
{
public:
	~Fire();
	Fire();

	Fire(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);

private:
	float _burnTime;
};


#endif //BOMBERMAN_FIRE_HPP
