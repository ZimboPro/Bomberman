//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_HEALTHBLOCK_HPP
#define BOMBERMAN_HEALTHBLOCK_HPP

#include "game_elements/VisibleGameObject.hpp"

class HealthBlock: public VisibleGameObject {
public:
	HealthBlock();
	HealthBlock(HealthBlock const & src);
	~HealthBlock();

	HealthBlock(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};


#endif //BOMBERMAN_HEALTHBLOCK_HPP
