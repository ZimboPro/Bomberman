//
// Created by Patrick RUSSELL on 2018/09/13.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP


#include <game_elements/VisibleGameObject.hpp>

class Bomb: public VisibleGameObject
{
public:
	~Bomb();
	Bomb();

	Bomb(Model_Texture & texture, float x, float y);
	BoundingBox getBoundingBox();

	void Update(float & timeElapsed);

private:
	float _timeTillExplode;
};


#endif //BOMBERMAN_BOMB_HPP
