//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_POWERBLOCK_HPP
#define BOMBERMAN_POWERBLOCK_HPP

#include <game_elements/VisibleGameObject.hpp>

class PowerBlock: public VisibleGameObject {
public:
	PowerBlock();
	PowerBlock(PowerBlock const & src);
	~PowerBlock();
	PowerBlock(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);
	BoundingBox getBoundingBox();

private:
	float _speed;
};


#endif //BOMBERMAN_POWERBLOCK_HPP
