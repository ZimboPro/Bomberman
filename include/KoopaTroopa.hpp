//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_KOOPATROOPA_HPP
#define BOMBERMAN_KOOPATROOPA_HPP

#include "VisibleGameObject.hpp"

class KoopaTroopa: public VisibleGameObject {
public:
	~KoopaTroopa();
	KoopaTroopa();

	KoopaTroopa(Model_Texture & texture, float x, float y);

	void Update(float & timeElapsed);

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};


#endif //BOMBERMAN_KOOPATROOPA_HPP
