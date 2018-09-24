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
	Goomba(Model_Texture & texture, float x, float y);
	Goomba(std::vector<Model_Texture *> & textures, float x, float y);
	Goomba(Goomba const & src);
	~Goomba();

	BoundingBox getBoundingBox();
	virtual void Draw(Shaders & shader);

	void Update(float & timeElapsed);
	// void Delay(void);

private:
	void dying(float & timeElapsed);
	void RandomDirection();
	void Move(float x, float y, float z);
	void Rotate(float degrees);
	float _speed;
	int	_directionGen = rand() % 4 + 1;
	float _time;
	float _totalElapsed;
	std::vector<Model_Sprite *> _models;
	int _index;
	
};

#endif //BOMBERMAN_GOOMBA_H
