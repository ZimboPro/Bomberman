//
// Created by Patrick RUSSELL on 2018/09/10.
//

#ifndef BOMBERMAN_GOOMBA_H
#define BOMBERMAN_GOOMBA_H

#include "VisibleGameObject.hpp"
/*
** Goomba class inherits from VisibleGameObject
*/
class Goomba: public VisibleGameObject
{
public:
	// Default Goomba constructor
	Goomba();
	// Goomba constructor - takes in reference to model texture as well as x and y position of the model
	Goomba(Model_Texture & texture, float x, float y);
	// Goomba constructor - takes in a reference to a vector of model texture pointers and the x and y of each model
	Goomba(std::vector<Model_Texture *> & textures, float x, float y);
	// Goomba copy contructor - to ensure it conforms to Coplien form
	Goomba(Goomba const & src);
	// Goomba destructor
	~Goomba();

	// Bounding box for Goomba object
	BoundingBox getBoundingBox();
	// 
	virtual void Draw(Shaders & shader);

	void Update(float & timeElapsed);

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

#endif //BOMBERMAN_GOOMBA_H
