//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_GOOMBA_H
#define BOMBERMAN_GOOMBA_H

#include "VisibleGameObject.hpp"

class Goomba: public VisibleGameObject
{
public:
	Goomba();
	Goomba(Goomba const & src);
	~Goomba();

	Goomba(Model_Texture & texture, float x, float y);
	BoundingBox getBoundingBox();

	void Update(float & timeElapsed);

private:
	float _speed;
	
};

#endif //BOMBERMAN_GOOMBA_H
