//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_POWERBLOCK_HPP
#define BOMBERMAN_POWERBLOCK_HPP

#include <VisibleGameObject.hpp>

class PowerBlock: public VisibleGameObject {
public:
	~PowerBlock();
	PowerBlock();

	PowerBlock(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};


#endif //BOMBERMAN_POWERBLOCK_HPP
