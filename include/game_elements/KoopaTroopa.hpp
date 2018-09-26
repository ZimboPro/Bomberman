//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_KOOPATROOPA_HPP
#define BOMBERMAN_KOOPATROOPA_HPP

#include "VisibleGameObject.hpp"

class KoopaTroopa: public VisibleGameObject {
public:
	KoopaTroopa();
	KoopaTroopa(Model_Texture & texture, float x, float y);
	KoopaTroopa(std::vector<Model_Texture *> & textures, float x, float y);
	KoopaTroopa(KoopaTroopa const & src);
	~KoopaTroopa();

	BoundingBox getBoundingBox();
	virtual void Draw(Shaders & shader);

	void Update(float & timeElapsed);
	// void Delay(void);

private:
	void dying(float & timeElapsed);
	void RandomDirection();
	void Move(float x, float y, float z = 0);
	void Rotate(float degrees);
	void newDirection();
	void movement(float degree, float moveX, float moveY, float boxX, float boxY, BoundingBox box);
	void init();
	void CheckDirection(BoundingBox box, float x, float y, std::vector<int> & dir, int d);
	void ShiftBox(BoundingBox & box, float x, float y);

	float _speed;
	int	_directionGen;
	float _time;
	float _totalElapsed;
	std::vector<Model_Sprite *> _models;
	int _index;
};


#endif //BOMBERMAN_KOOPATROOPA_HPP
